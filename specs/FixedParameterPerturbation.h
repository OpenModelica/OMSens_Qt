#ifndef FIXEDPARAMETERPERTURBATION_H
#define FIXEDPARAMETERPERTURBATION_H

#include <QString>

class FixedParameterPerturbation
{
public:
    FixedParameterPerturbation(QString name, double value);
    QString name;
    double value;
};

#endif // FIXEDPARAMETERPERTURBATION_H
