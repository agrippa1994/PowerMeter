#include "obddatahandler.h"
#include <QList>

OBDDataHandler::OBDDataHandler(QObject *parent) : QObject(parent)
{

}

void OBDDataHandler::handleData(const QByteArray &buffer)
{
    data += buffer;
    QList<QByteArray> messages = data.split('\n');

}
