#include "application.h"
#include "obdsocket.h"
#include <QQuickWindow>
#include <QQmlContext>
#include <QQmlApplicationEngine>

Application::Application(QObject *parent)
    : QObject(parent),
      socket(new OBDSocket(this)),
      engine(new QQmlApplicationEngine(this))
{
    // Load Engine
    qmlRegisterType<Application>("OBDApplication", 1, 0, "OBDApplication");
    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));

    engine->rootContext()->setContextProperty("application", this);

    QObject::connect(socket, &OBDSocket::stringRead, [&](const QString& text) {
        setLabelColor("orange");
        setLabel(text);
    });

    QObject::connect(socket, &OBDSocket::powerRead, [&](double power) {
        setLabelColor("white");
        setPowerValue(power);
    });

    QObject::connect(socket, &OBDSocket::speedRead, [&](double speed) {
        setSpeedValue(speed);
    });

    QObject::connect(socket, &OBDSocket::stateChanged, [&](OBDSocket::SocketState state) {
        bool shouldReconnect = false;
        switch(state)
        {
        case OBDSocket::UnconnectedState:
            shouldReconnect = true;
            setLabelColor("red");
            setLabel("Unverbunden");
            break;
        case OBDSocket::HostLookupState:
            setLabelColor("yellow");
            setLabel("Auflösen ...");
            break;
        case OBDSocket::ConnectingState:
            setLabelColor("yellow");
            setLabel("Verbinden ...");
            break;
        case OBDSocket::ConnectedState:
            setLabelColor("green");
            setLabel("Verbunden");
            break;
        case OBDSocket::ClosingState:
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

Application::~Application()
{
    delete socket;
    delete engine;
}

void Application::reconnect()
{
    if(socket->state() != OBDSocket::UnconnectedState) {
        socket->abort();
    }

    //socket->connectToHost("192.168.56.101", 35000);
    socket->connectToHost("192.168.0.10", 35000);
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

void Application::setSpeedValue(double value)
{
    setProperty("speedValue", value);
}

void Application::setProperty(const char *name, const QVariant &value)
{
    QQuickWindow *window;
    if((window = getQuickWindow()))
        window->setProperty(name, value);
}

QQuickWindow *Application::getQuickWindow()
{
    if(engine->rootObjects().size() > 0)
        return qobject_cast<QQuickWindow *>(engine->rootObjects()[0]);

    return 0;
}

