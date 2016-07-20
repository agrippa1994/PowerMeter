#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "obdrequest.h"
#include "obddatahandler.h"
#include "application.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Application a;

    OBDDataHandler dh;
    dh.handleData(QByteArray("41 00 00 00\n<"));

    qDebug() << OBDRequest(OBDPID::availablePids()[OBDPIDID::MAF]).getRequestString();
    //qDebug() << OBDRequest(Mode01, MAF).stringValue();

    return app.exec();
}
