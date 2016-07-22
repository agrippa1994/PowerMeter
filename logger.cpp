#include "logger.h"

Logger &Logger::sharedLogger()
{
    static Logger l;
    return l;
}

QString Logger::getBuffer() const
{
    return buffer;
}

Logger::Logger()
{
    qInstallMessageHandler([](QtMsgType type, const QMessageLogContext &ctx, const QString &text) {
        Logger::sharedLogger().messageHandler(type, ctx, text);
    });
}

void Logger::messageHandler(QtMsgType, const QMessageLogContext &, const QString &text)
{
    buffer.append(text + '\n');
    emit messageLogged();
}
