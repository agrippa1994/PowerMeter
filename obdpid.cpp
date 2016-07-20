#include "obdpid.h"

OBDPID::OBDPID(OBDMode mode, OBDPIDID pid, int length)
    : mode(mode), pid(pid), length(length)
{

}

OBDPID::OBDPID()
{

}

const QMap<OBDPIDID, OBDPID> &OBDPID::availablePids()
{
    static QMap<OBDPIDID, OBDPID> pids({
        { OBDPIDID::MAF, OBDPID(OBDMode::Mode01, OBDPIDID::MAF, 2) }
    });

    return pids;
}

OBDMode OBDPID::getMode() const
{
    return mode;
}

OBDPIDID OBDPID::getPid() const
{
    return pid;
}

int OBDPID::getLength() const
{
    return length;
}
