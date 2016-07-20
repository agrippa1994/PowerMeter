#ifndef OBDDATAHANDLER_H
#define OBDDATAHANDLER_H

#include <QObject>

class OBDDataHandler : public QObject
{
    Q_OBJECT
public:
    explicit OBDDataHandler(QObject *parent = 0);

    void handleData(const QByteArray& buffer);
signals:
    void obdReady();

private:
    QByteArray data;
};

#endif // OBDDATAHANDLER_H
