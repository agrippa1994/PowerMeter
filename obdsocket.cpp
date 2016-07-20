#include "obdsocket.h"
#include <QList>

OBDSocket::OBDSocket(QObject *parent)
    : QTcpSocket(parent)
{

    QObject::connect(this, &QTcpSocket::readyRead, [&]() {
        buffer += readAll();
        QList<QByteArray> splitted = buffer.split('\n');

    });
}
