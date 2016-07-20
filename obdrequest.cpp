#include "obdrequest.h"

OBDRequest::OBDRequest(const OBDPID &pid)
{
    requestString.sprintf("%02X %02X\r", pid.getMode(), pid.getPid());
}

const QString &OBDRequest::getRequestString() const
{
    return requestString;
}
