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
        }

        QTimer::singleShot(5, [=]() {
            // Read lines
            for(const QString& line : data) {
                std::vector<int> bytes;

                // Parse bytes
                for(QString token : line.split(' ', QString::SkipEmptyParts)) {
                    bool ok = false;
                    int parsed = token.toInt(&ok, 16);
                    if(ok) {
                        bytes.push_back(parsed);
                    }
                    else {
                        if(line != ">" && line.length() > 0)
                            emit stringRead(line);
                        break;
                    }
                }

                // 2 Byte (41 PID)
                if(bytes.size() > 2) {
                    qDebug() << "Read Bytes: " << bytes;

                    if(bytes[0] == 0x41) { // Check response code
                        // Calculate MAF and HP
                        if(bytes.size() == 4) {
                            if(bytes[1] == 0x10) { // MAF
                                double maf = (double)(256.0 * bytes[2] + bytes[3]) / 100.0;
                                emit powerRead(maf / 15.2 * 46.0 * 0.33 * 1.34);
                            }
                        }
                        if(bytes.size() == 3) {
                            if(bytes[1] == 0x11) { // Throttle
                                emit throttleRead((double)bytes[2] * (100.0/255.0));
                            }
                            if(bytes[1] == 0x0D) { // Speed
                                emit speedRead((double)bytes[2]);
                            }
                        }
                    }
                }
            }

            // Request next value
            int req = nextRequest;
            if(nextRequest == 0x10) req = 0x11;
            if(nextRequest == 0x11) req = 0x0D;
            if(nextRequest == 0x0D) req = 0x10;
            nextRequest = req;

            send(QString().sprintf("01 %02X 1", nextRequest));
        });
    });

}

bool OBDSocket::send(const QString &data)
{
    qDebug() << "send: " << data;
    if(obdReady) {
        obdReady = false;
        return write((data + "\r").toStdString().c_str()) > 0;
    }

    return false;
}
