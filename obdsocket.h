#ifndef OBDSOCKET_H
#define OBDSOCKET_H
#include <QTcpSocket>

class OBDSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit OBDSocket(QObject *parent = 0);

signals:
    void powerRead(double power);
    void throttleRead(double throttle);
    void speedRead(double speed);
    void stringRead(const QString& text);

private:
    int nextRequest = 0x10;

    bool obdReady = false;
    bool send(const QString& data);

};

#endif // OBDSOCKET_H
