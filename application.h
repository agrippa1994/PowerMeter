#ifndef APPLICATION_H
#define APPLICATION_H
#include <QObject>

class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = 0);
    ~Application();

    Q_INVOKABLE void reconnect();

    void setPowerValue(double value);
    void setLabel(const QString& text);
    void setAnimationDuration(int duration);
    void setLabelColor(const QString& color);
    void setSpeedValue(double value);
    void setProperty(const char *name, const QVariant &value);

    class QQuickWindow *getQuickWindow();

private:
    class OBDSocket *socket;
    class QQmlApplicationEngine *engine;
};

#endif // APPLICATION_H
