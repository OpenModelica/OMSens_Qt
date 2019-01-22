#ifndef INDIVSPECS_H
#define INDIVSPECS_H

#include "RunSpecifications.h"
#include <QString>
#include <QStringList>
#include <QJsonDocument>

class IndivSpecs : public RunSpecifications
{
public:
    IndivSpecs(QJsonDocument json_specs_doc);
    IndivSpecs(QString model_file_path, QString model_name, QStringList parameters_to_perturb,
               double percentage, double start_time, double stop_time,
               QStringList vars_to_analyze);
    // Methods
    QJsonDocument toJson();
private:
    // Specification info
    QString model_file_path;
    QString model_name;
    QStringList parameters_to_perturb;
    double percentage;
    double start_time;
    double stop_time;
    QStringList vars_to_analyze;
    // Auxs
    QList<QString> fromListOfVariantToListOfStr(QList<QVariant> listOfQVariant);
};

#endif // INDIVSPECS_H
