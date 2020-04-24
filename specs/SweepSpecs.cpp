#include "SweepSpecs.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QList>

// Conventions
const QString SweepSpecs::analysis_id_str = "sweep";

// Constructors
SweepSpecs::SweepSpecs(QJsonDocument json_specs_doc)
{
    // Get main object from document
    QJsonObject json_specs = json_specs_doc.object();
    // Simple data
    this->model_name          = json_specs.value(QString("model_name")).toString();
    this->model_file_path     = json_specs.value(QString("model_mo_path")).toString();
    this->start_time          = json_specs.value(QString("start_time")).toDouble();
    this->stop_time           = json_specs.value(QString("stop_time")).toDouble();
    this->vars_to_analyze     = json_specs.value(QString("vars_to_analyze")).toVariant().toStringList();
    this->plot_upper_lower_limit = json_specs.value(QString("plot_upper_lower_limit")).toBool();

    // Complex data
    // Sweep params
    QJsonArray sweep_params_jsonarray = json_specs.value(QString("parameters_to_sweep")).toArray();
    this->parameters_to_sweep = fromQJsonArrayToSweepingPerts(sweep_params_jsonarray);

    // Fixed params
    QJsonArray fixed_params_jsonarray = json_specs.value(QString("fixed_params")).toArray();
    this->fixed_params        =  fromQJsonArrayToFixedPerts(fixed_params_jsonarray);;
}

SweepSpecs::SweepSpecs(QString model_file_path,
    QString model_name,
    double start_time,
    double stop_time,
    QStringList vars_to_analyze,
    QList<SweepingParameterPerturbation> parameters_to_sweep,
    QList<FixedParameterPerturbation> fixed_params,
    bool plot_upper_lower_limit
    ):
        fixed_params(fixed_params),
        parameters_to_sweep(parameters_to_sweep),
        model_file_path(model_file_path),
        model_name(model_name),
        start_time(start_time),
        stop_time(stop_time),
        vars_to_analyze(vars_to_analyze),
        plot_upper_lower_limit(plot_upper_lower_limit)
{
    // Do nothing else for now
}

// Methods
QList<FixedParameterPerturbation> SweepSpecs::fromQJsonArrayToFixedPerts(QJsonArray fixed_params_jsonarray)
{
    QList<FixedParameterPerturbation> fixed_perts;
    foreach (QJsonValue jsonVal, fixed_params_jsonarray) {
        // Get object info
        QString name = jsonVal.toObject().value(QString("name")).toString();
        double value = jsonVal.toObject().value(QString("value")).toDouble();
        // Initialize instance
        FixedParameterPerturbation sweeping_param_pert = FixedParameterPerturbation(name, value);
        fixed_perts.append(sweeping_param_pert);
    }

    return fixed_perts;
}

QJsonArray SweepSpecs::fromSweepingPertsToQJsonArray(QList<SweepingParameterPerturbation> parameters_to_sweep)
{
    QJsonArray sweep_params_jsonarray;
    foreach (SweepingParameterPerturbation sweepPert,  parameters_to_sweep){
        // Get object info
        QString name = sweepPert.name;
        double delta_percentage = sweepPert.delta_percentage;
        int iterations          = sweepPert.iterations;
        // Initialize object
        QJsonObject sweep_info;
        sweep_info["name"]              = name;
        sweep_info["delta_percentage"]  = delta_percentage;
        sweep_info["iterations"]        = iterations;
        sweep_params_jsonarray.append(sweep_info);
    }

    return sweep_params_jsonarray;
}

QJsonArray SweepSpecs::fromFixedPertsToQJsonArray(QList<FixedParameterPerturbation> fixed_params)
{
    QJsonArray fixed_params_jsonarray;
    foreach (FixedParameterPerturbation fixedPert,  fixed_params){
        // Get object info
        QString name = fixedPert.name;
        double value = fixedPert.value;
        // Initialize object
        QJsonObject fixed_pert_info;
        fixed_pert_info["name"]              = name;
        fixed_pert_info["value"]  = value;
        fixed_params_jsonarray.append(fixed_pert_info);
    }
    return fixed_params_jsonarray;
}

QJsonDocument SweepSpecs::toJson()
{
    // Initialize JSON root object
    QJsonObject json_specs;
    // Specify analysis type
    json_specs["analysis_type"]         = this->analysis_id_str;
    // Add specs to json
    json_specs["model_name"]            = this->model_name;
    json_specs["model_mo_path"]         = this->model_file_path;
    json_specs["start_time"]            = this->start_time;
    json_specs["stop_time"]             = this->stop_time;
    json_specs["parameters_to_sweep"]   = fromSweepingPertsToQJsonArray(this->parameters_to_sweep);
    json_specs["fixed_params"]          = fromFixedPertsToQJsonArray(this->fixed_params);
    json_specs["vars_to_analyze"]       = QJsonArray::fromStringList(this->vars_to_analyze);
    json_specs["plot_upper_lower_limit"]= this->plot_upper_lower_limit;
    // Initialize JSON doc from JSON object
    QJsonDocument json_specs_doc(json_specs);

    return json_specs_doc;
}

QList<SweepingParameterPerturbation> SweepSpecs::fromQJsonArrayToSweepingPerts(QJsonArray sweep_params_jsonarray)
{
    QList<SweepingParameterPerturbation> sweeping_perts;
    foreach (QJsonValue jsonVal, sweep_params_jsonarray) {
        // Get object info
        QString name            = jsonVal.toObject().value(QString("name")).toString();
        double delta_percentage = jsonVal.toObject().value(QString("delta_percentage")).toDouble();
        int iterations          = jsonVal.toObject().value(QString("iterations")).toInt();
        // Initialize instance
        SweepingParameterPerturbation sweeping_param_pert = SweepingParameterPerturbation(name, delta_percentage, iterations);
        sweeping_perts.append(sweeping_param_pert);
    }

    return sweeping_perts;
}
