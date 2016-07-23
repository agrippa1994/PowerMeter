#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "application.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Application a;

    return app.exec();
}
