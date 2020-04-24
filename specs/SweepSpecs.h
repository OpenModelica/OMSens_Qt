#ifndef SWEEPSPECS_H
#define SWEEPSPECS_H

#include "RunSpecifications.h"
#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonArray>

// Aux structs
struct FixedParameterPerturbation {
    FixedParameterPerturbation(QString name, double value): name(name), value(value) {}
    QString name;
    double value;
};

struct SweepingParameterPerturbation {
    QString name;
    double delta_percentage;
    int iterations;
    SweepingParameterPerturbation(QString name, double delta_percentage, int iterations):
        name(name), delta_percentage(delta_percentage), iterations(iterations) {}
};
// Class
class SweepSpecs : public RunSpecifications
{
public:
    // Constructors
    SweepSpecs(QJsonDocument json_specs_doc);
    SweepSpecs(QString model_file_path, QString model_name, double start_time, double stop_time,
               QStringList vars_to_analyze, QList<SweepingParameterPerturbation> parameters_to_sweep,
               QList<FixedParameterPerturbation> fixed_params, bool plot_upper_lower_limit);

    // Conventions
    static const QString analysis_id_str; // Defined in .cpp

    // Methods
    QJsonDocument toJson();

    // Specification info
    QList<FixedParameterPerturbation>    fixed_params;
    QList<SweepingParameterPerturbation> parameters_to_sweep;
    QString model_file_path;
    QString model_name;
    double start_time;
    double stop_time;
    QStringList vars_to_analyze;
    bool plot_upper_lower_limit;

private:
    // Methods
    void fromJsonArrayToListOfSweepingPerts(QJsonArray params_to_sweep_jsonarray);
    QList<SweepingParameterPerturbation> fromQJsonArrayToSweepingPerts(QJsonArray sweep_params_jsonarray);
    QList<FixedParameterPerturbation> fromQJsonArrayToFixedPerts(QJsonArray fixed_params_jsonarray);
    QJsonArray fromSweepingPertsToQJsonArray(QList<SweepingParameterPerturbation> parameters_to_sweep);
    QJsonArray fromFixedPertsToQJsonArray(QList<FixedParameterPerturbation> fixed_params);
};

#endif // SWEEPSPECS_H
