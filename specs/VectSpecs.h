#ifndef VECTSPECS_H
#define VECTSPECS_H

#include <QString>
#include <QJsonDocument>
#include <QStringList>

// Enum
enum OptimType {MaxOptim, MinOptim};

// Class
class VectSpecs
{
public:
    // Constructors
    VectSpecs(QJsonDocument json_specs_doc);
    VectSpecs( QString model_file_path, QString model_name, OptimType optim_type,
               QStringList parameters_to_perturb, double epsilon, double percentage, double start_time,
               double stop_time, QString target_var);

    // Methods
    QJsonDocument toJson();

    // Conventions
    static const QString analysis_id_str; // Defined in .cpp

    // Specification info
    QString model_file_path;
    QString model_name;
    OptimType optim_type;
    QStringList parameters_to_perturb;
    double epsilon;
    double percentage;
    double start_time;
    double stop_time;
    QString target_var;
    QString optimTypeString(OptimType optim_type);

private:
    // Auxs
    QList<QString> fromListOfVariantToListOfStr(QList<QVariant> listOfQVariant);
    void optimTypeString(QJsonObject json_specs);
};

#endif // VECTSPECS_H
