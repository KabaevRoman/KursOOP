#ifndef STATEDATA_H
#define STATEDATA_H

#include <QObject>

struct TStateData
{
    bool washer;//если мойка свободна true else false;
    bool worker;//если мастер свободен true else false;
};

#endif // STATEDATA_H
