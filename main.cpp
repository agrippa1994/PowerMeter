#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "application.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Application a;

    return app.exec();
}
