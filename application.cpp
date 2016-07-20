#include "application.h"
#include <QQuickItem>
#include <QQuickWindow>
#include <QTimer>

Application::Application(QObject *parent) : QObject(parent)
{
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    setLabel("Verbunden");
    setLabelColor("green");
    setPowerValue(100);

    QTimer *timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, [&]() {
        setPowerValue(rand() % 130);
    });

    timer->start(250);
    QObject::connect(&socket, &QTcpSocket::readyRead, [&]() {

    });

    QObject::connect(&socket, &QTcpSocket::stateChanged, [&](QAbstractSocket::SocketState state) {
        switch(state)
        {
        case QAbstractSocket::UnconnectedState:
            setLabelColor("red");
            setLabel("Unverbunden");
            break;
        case QAbstractSocket::HostLookupState:
            setLabelColor("yellow");
            setLabel("Auflösen ...");
            break;
        case QAbstractSocket::ConnectingState:
            setLabelColor("yellow");
            setLabel("Verbinden ...");
            break;
        case QAbstractSocket::ConnectedState:
            setLabelColor("green");
            setLabel("Verbunden");
            break;
        case QAbstractSocket::ClosingState:
            setLabelColor("red");
            setLabel("Schließt ...");
            break;
        default:
            setLabelColor("red");
            setLabel("Unbekannt");
            break;
        }
    });

    socket.connectToHost("192.168.0.100", 35000);
}

void Application::setPowerValue(int value)
{
    setProperty("gaugeValue", value);
}

void Application::setLabel(const QString &text)
{
    setProperty("labelText", text);
}

void Application::setLabelColor(const QString &color)
{
    setProperty("labelColor", color);
}

void Application::setProperty(const char *name, const QVariant &value)
{
    QQuickWindow *window;
    if((window = getQuickWindow()))
        window->setProperty(name, value);
}

QQuickWindow *Application::getQuickWindow()
{
    if(engine.rootObjects().size() > 0)
        return qobject_cast<QQuickWindow *>(engine.rootObjects()[0]);

    return 0;
}

