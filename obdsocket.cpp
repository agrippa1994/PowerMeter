#include "obdsocket.h"
#include <QList>
#include <vector>

OBDSocket::OBDSocket(QObject *parent)
    : QTcpSocket(parent)
{

    QObject::connect(this, &QTcpSocket::stateChanged, [&](QTcpSocket::SocketState state) {
        if(state == QTcpSocket::ConnectedState) {
            write("AT Z\r");
        }
    });
    QObject::connect(this, &QTcpSocket::readyRead, [&]() {
        QList<QByteArray> data = readAll().split('\r');
        if(data.size() == 0)
            return;

        if(data.last() == ">")
            obdReady = true;

        // Read lines
        for(const QByteArray& line : data) {
            std::vector<int> bytes;
            QList<QByteArray> tokens = line.split(' ');

            // Parse bytes
            for(QByteArray token : line.split(' ')) {
                bool ok = false;
                int parsed = token.toInt(&ok, 16);
                if(ok)
                    bytes.push_back(parsed);
            }

            // Calculate MAF and HP
            if(bytes.size() == 4) {
                if(bytes[0] == 0x41 && bytes[1] == 0x10) {
                    double maf = (double)(256.0 * bytes[2] + bytes[3]) / 4.0;
                    double hp = maf / 15.2 * 46.0 * 0.33 * 1.34;
                    emit powerRead(hp);
                }
            }
        }

        // Request MAF again
        send("01 10 1");
    });
}

bool OBDSocket::send(const QString &data)
{
    if(obdReady)
        return write((data + "\r").toStdString().c_str()) > 0;

    return false;
}