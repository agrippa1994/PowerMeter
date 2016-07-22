#ifndef OBDSOCKET_H
#define OBDSOCKET_H
#include <QTcpSocket>
#include <QString>

class OBDSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit OBDSocket(QObject *parent = 0);

signals:
    void powerRead(double power);
    void stringRead(const QString& text);

private:
    bool obdReady = false;

    bool send(const QString& data);

};

#endif // OBDSOCKET_H
