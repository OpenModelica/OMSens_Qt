#ifndef VECTSPECS_H
#define VECTSPECS_H

#include <QString>
#include <QJsonDocument>
#include <QStringList>

// Class
class VectSpecs
{
public:
    // Constructors
    VectSpecs(QJsonDocument json_specs_doc);
    VectSpecs( QString model_file_path, QString model_name, bool maximize,
               QStringList parameters_to_perturb, double epsilon, double percentage, double start_time,
               double stop_time, QString target_var);

    // Methods
    QJsonDocument toJson();

    // Conventions
    static const QString analysis_id_str; // Defined in .cpp

    // Specification info
    QString model_file_path;
    QString model_name;
    bool maximize;
    QStringList parameters_to_perturb;
    double epsilon;
    double percentage;
    double start_time;
    double stop_time;
    QString target_var;
    QString optimTypeString(bool maximize);

private:
    // Auxs
    QList<QString> fromListOfVariantToListOfStr(QList<QVariant> listOfQVariant);
    bool ifMaximizationFromMaxOrMinStr(QString max_or_min);
};

#endif // VECTSPECS_H
