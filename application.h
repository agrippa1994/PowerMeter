#ifndef APPLICATION_H
#define APPLICATION_H
#include "obdsocket.h"
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QTcpSocket>

class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = 0);

    Q_INVOKABLE void reconnect();

    void setPowerValue(double value);
    void setLabel(const QString& text);

    void setLabelColor(const QString& color);
    void setProperty(const char *name, const QVariant &value);

    QQuickWindow *getQuickWindow();

private:
    QQmlApplicationEngine engine;
    OBDSocket socket;
};

#endif // APPLICATION_H
