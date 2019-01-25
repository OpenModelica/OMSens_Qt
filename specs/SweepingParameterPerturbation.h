#ifndef SWEEPINGPARAMETERPERTURBATION_H
#define SWEEPINGPARAMETERPERTURBATION_H

#include <QString>

class SweepingParameterPerturbation
{
public:
    SweepingParameterPerturbation(QString name, double delta_percentage, int iterations);
    QString name;
    double delta_percentage;
    int iterations;
};

#endif // SWEEPINGPARAMETERPERTURBATION_H
