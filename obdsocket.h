#ifndef OBDSOCKET_H
#define OBDSOCKET_H
#include <QTcpSocket>

class OBDSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit OBDSocket(QObject *parent = 0);

private:
    QByteArray buffer;

};

#endif // OBDSOCKET_H
