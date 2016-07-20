#ifndef OBDPID_H
#define OBDPID_H
#include "obd.h"
#include <QMap>

class OBDPID
{

public:
    explicit OBDPID(OBDMode mode, OBDPIDID pid, int length);
    OBDPID();

    static const QMap<OBDPIDID, OBDPID>& availablePids();

    OBDMode getMode() const;
    OBDPIDID getPid() const;
    int getLength() const;

private:
    int length = 0;
    OBDMode mode;
    OBDPIDID pid;
};

#endif // OBDPID_H
