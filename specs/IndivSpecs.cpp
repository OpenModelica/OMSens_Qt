#include "IndivSpecs.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QList>

// Conventions
const QString IndivSpecs::analysis_id_str = "indiv";

// Constructors
IndivSpecs::IndivSpecs(QJsonDocument json_specs_doc)
{
    // Get main object from document
    QJsonObject json_specs = json_specs_doc.object();
    //
    this->model_name      = json_specs.value(QString("model_name")).toString();
    this->model_file_path = json_specs.value(QString("model_mo_path")).toString();
    this->percentage      = json_specs.value(QString("percentage")).toDouble();
    this->start_time      = json_specs.value(QString("start_time")).toDouble();
    this->stop_time       = json_specs.value(QString("stop_time")).toDouble();

    // Get variables QVariant list
    QList<QVariant> variablesQVariant = json_specs.value(QString("vars_to_analyze")).toArray().toVariantList();

    // Transform from list of QVariant to list of QString
    this->vars_to_analyze = fromListOfVariantToListOfStr(variablesQVariant);

    // Get parameters QVariant list
    QList<QVariant> parametersQVariant = json_specs.value(QString("parameters_to_perturb")).toArray().toVariantList();

    // Transform from list of QVariant to list of QString
    this->parameters_to_perturb = fromListOfVariantToListOfStr(parametersQVariant);
}

IndivSpecs::IndivSpecs(QString model_file_path, QString model_name, QStringList parameters_to_perturb,
               double percentage, double start_time, double stop_time,
               QStringList vars_to_analyze):  model_file_path(model_file_path), model_name(model_name),
                                              parameters_to_perturb(parameters_to_perturb),
                                              percentage(percentage), start_time(start_time),
                                              stop_time(stop_time), vars_to_analyze(vars_to_analyze)
{
    // Do nothing else for now
}

// Methods
QJsonDocument IndivSpecs::toJson()
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
    json_specs["percentage"]            = this->percentage;
    json_specs["vars_to_analyze"]       = QJsonArray::fromStringList(this->vars_to_analyze);
    json_specs["parameters_to_perturb"] = QJsonArray::fromStringList(this->parameters_to_perturb);
    // Initialize JSON doc from JSON object
    QJsonDocument json_specs_doc(json_specs);

    return json_specs_doc;
}

// Auxs
QList<QString> IndivSpecs::fromListOfVariantToListOfStr(QList<QVariant> listOfQVariant)
{
    QList<QString> listOfStr;
    foreach (QVariant objQVariant, listOfQVariant) {
        QString objStr = objQVariant.toString();
        listOfStr.append(objStr);
    }
    return listOfStr;
}
