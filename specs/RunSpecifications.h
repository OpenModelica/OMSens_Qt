#ifndef RUNSPECIFICATION_H
#define RUNSPECIFICATION_H

#include <QJsonDocument>

class RunSpecifications
{
public:
    virtual QJsonDocument toJson() = 0;
};

#endif // RUNSPECIFICATION_H
