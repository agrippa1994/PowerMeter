#include "obdsocket.h"
#include <QList>
#include <vector>
#include <QTimer>

OBDSocket::OBDSocket(QObject *parent)
    : QTcpSocket(parent)
{

    QObject::connect(this, &QTcpSocket::stateChanged, [&](QTcpSocket::SocketState state) {
        if(state == QTcpSocket::ConnectedState) {
            obdReady = true;
            qDebug() << "Write " << send("AT Z");
        } else {
            obdReady = false;
        }
    });

    QObject::connect(this, &QTcpSocket::readyRead, [&]() {
        QList<QString> data = QString(readAll()).split("\r\n", QString::SkipEmptyParts);
        qDebug() << "Read: " << data;
        if(data.size() == 0)
            return;

        if(data.contains(">")) {
            obdReady = true;
            QTimer::singleShot(10, [=]() {
                // Read lines
                for(const QString& line : data) {
                    std::vector<int> bytes;

                    // Parse bytes
                    for(QString token : line.split(' ')) {
                        bool ok = false;
                        int parsed = token.toInt(&ok, 16);
                        if(ok) {
                            bytes.push_back(parsed);
                        }
                        else {
                            emit stringRead(line);
                            break;
                        }
                    }

                    qDebug() << "Read Bytes: " << bytes;
                    // Calculate MAF and HP
                    if(bytes.size() == 4) {
                        if(bytes[0] == 0x41 && bytes[1] == 0x10) {
                            double maf = (double)(256.0 * bytes[2] + bytes[3]) / 4.0;
                            qDebug() << "Read MAF: " << maf;
                            double hp = maf / 15.2 * 46.0 * 0.33 * 1.34;
                            emit powerRead(hp);
                        }
                    }
                }

                // Request MAF again
                send("01 10 1");
            });
        }
    });
}

bool OBDSocket::send(const QString &data)
{
    if(obdReady) {
        return write((data + "\r").toStdString().c_str()) > 0;
        obdReady = false;
    }

    return false;
}
