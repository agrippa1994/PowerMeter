#ifndef OBDREQUEST_H
#define OBDREQUEST_H
#include "obdpid.h"
#include <QString>

class OBDRequest
{
public:
    OBDRequest(const OBDPID& pid);

    const QString& getRequestString() const;

private:
    QString requestString;
};

#endif // OBDREQUEST_H
