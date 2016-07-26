#include "obdsocket.h"

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
        // Read all data and split lines
        QList<QString> data = QString(readAll()).split("\r\n", QString::SkipEmptyParts);

        if(data.size() == 0)
            return;

        qDebug() << "Read: " << data;

        if(data.last() == ">") {
            obdReady = true;
        }

        // Read lines
        for(const QString& line : data) {
            QList<int> bytes;
            bytes.reserve(4); // Reserve space for 4 ints

            // Parse bytes
            for(QString token : line.split(' ', QString::SkipEmptyParts)) {
                bool ok = false;
                int parsed = token.toInt(&ok, 16);
                if(ok) {
                    bytes << parsed; // Append parsed byte
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
                            emit speedRead((double)bytes[2] * 1.05);
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

        if(send(QString().sprintf("01 %02X 1", nextRequest)))
            nextRequest = req;
    });
}

bool OBDSocket::send(const QString &data)
{
    if(obdReady) {
        obdReady = false;
        qDebug() << "send: " << data;
        return write((data + "\r").toStdString().c_str()) > 0;
    }

    return false;
}
