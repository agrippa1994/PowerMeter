#include "application.h"
#include <QQuickItem>
#include <QQuickWindow>
#include <QTimer>
#include <QQmlContext>

Application::Application(QObject *parent)
    : QObject(parent)
{
    // Load Engine
    qmlRegisterType<Application>("OBDApplication", 1, 0, "OBDApplication");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    engine.rootContext()->setContextProperty("application", this);

    QObject::connect(&socket, &OBDSocket::stringRead, [&](const QString& text) {
        setLabel(text);
    });

    QObject::connect(&socket, &OBDSocket::powerRead, [&](double power) {
        setPowerValue(power);
    });

    QObject::connect(&socket, &QTcpSocket::stateChanged, [&](QAbstractSocket::SocketState state) {
        bool shouldReconnect = false;
        switch(state)
        {
        case QAbstractSocket::UnconnectedState:
            shouldReconnect = true;
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
            shouldReconnect = true;
            setLabelColor("red");
            setLabel("Unbekannt");
            break;
        }

        if(shouldReconnect) {
            reconnect();
        }
    });

    reconnect();
}

void Application::reconnect()
{
    if(socket.state() != OBDSocket::UnconnectedState) {
        socket.abort();
    }

    //socket.connectToHost("127.0.0.1", 8000);
    socket.connectToHost("192.168.0.10", 35000);
    qDebug() << "Trying to connect to OBD server ...";
}

void Application::setPowerValue(double value)
{
    setProperty("gaugeValue", value);
}

void Application::setLabel(const QString &text)
{
    setProperty("labelText", text);
}

void Application::setAnimationDuration(int duration)
{
    setProperty("animationDuration", duration);
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

