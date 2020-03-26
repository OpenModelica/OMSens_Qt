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
    VectSpecs(
        QString model_file_path,
        QString model_name, bool maximize,
        QStringList parameters_to_perturb,
        double epsilon,
        double percentage,
        double start_time,
        double stop_time,
        QString restriction_path,
        QString target_var,

        QString optimizer_name,
        QString objective_function_name,
        double alpha_value,
        QString constrained_time_path_file,
        QString constrained_variable,
        double constrained_epsilon,

        bool plot_restriction,
        bool plot_std_run
    );

    // Methods
    QJsonDocument toJson();

    // Conventions
    static const QString analysis_id_str; // Defined in .cpp

    // Specification info
    QString model_file_path;
    QString model_name;

    // Optimization info
    QString optimizer_name;
    QString objective_function_name;

    // Alpha weighted objective function for optimization
    double alpha_value;

    // Plot information
    bool plot_restriction;
    bool plot_std_run;

    // Single variable objective function for optimization
    QString target_var;
    QString optimTypeString(bool maximize);
    double percentage;

    // Required Additional simulation specs
    QStringList parameters_to_perturb;
    bool maximize;
    double epsilon;
    double start_time;
    double stop_time;
    QString restriction_path;

    // Optional Additional simulation specs
    QString constrained_time_path_file;
    QString constrained_variable;
    double constrained_epsilon;

private:
    // Auxs
    QList<QString> fromListOfVariantToListOfStr(QList<QVariant> listOfQVariant);
    bool ifMaximizationFromMaxOrMinStr(QString max_or_min);
};

#endif // VECTSPECS_H
