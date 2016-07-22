#ifndef LOG_H
#define LOG_H
#include <QtGlobal>
#include <QString>
#include <QObject>

class Logger : public QObject
{
    Q_OBJECT

public:
    static Logger& sharedLogger();

    QString getBuffer() const;

signals:
    void messageLogged();

private:
    QString buffer;

    Logger();

    void messageHandler(QtMsgType type, const QMessageLogContext &ctx, const QString &text);

};

void GlobalMessageHandler(QtMsgType type, const QMessageLogContext &ctx, const QString &text);
QString GetLog();

#endif // LOG_H
