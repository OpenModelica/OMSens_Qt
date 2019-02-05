#include "model.h"
#include <QList>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

// Constructors
Model::Model(QJsonDocument model_info_json)
{
    // Get main object from document
    QJsonObject json_info = model_info_json.object();
    // Initialize model from information found in json
    mInputVariables  = json_info.value(QString("input_variables")).toVariant().toStringList();
    mOutputVariables = json_info.value(QString("output_variables")).toVariant().toStringList();
    mAuxVariables    = json_info.value(QString("aux_variables")).toVariant().toStringList();
    mParameters      = json_info.value(QString("parameters")).toVariant().toStringList();
    mFilePath        = json_info.value(QString("model_mo_path")).toString();
    mModelName       = json_info.value(QString("model_name")).toString();

}

Model::Model(QList<QString> inputVariables, QList<QString> outputVariables, QList<QString> auxVariables, QList<QString> parameters, QString filePath, QString modelName):
  mInputVariables(inputVariables),
  mOutputVariables(outputVariables),
  mAuxVariables(auxVariables),
  mParameters(parameters),
  mFilePath(filePath),
  mModelName(modelName)
{
    // No code needed inside the class constructor for now
}

// ---- GETTERS ----
QList<QString> Model::getInputVariables() const
{
    return mInputVariables;
}

QList<QString> Model::getOutputVariables() const
{
    return mOutputVariables;
}

QList<QString> Model::getAuxVariables() const
{
    return mAuxVariables;
}

QList<QString> Model::getParameters() const
{
    return mParameters;
}

QString Model::getFilePath() const
{
    return mFilePath;
}

QString Model::getModelName() const
{
    return mModelName;
}

// To JSON
QJsonDocument Model::toJson()
{
    // Initialize JSON root object
    QJsonObject json_specs;
    json_specs["input_variables"]  = QJsonArray::fromStringList(mInputVariables);
    json_specs["output_variables"] = QJsonArray::fromStringList(mOutputVariables);
    json_specs["aux_variables"]    = QJsonArray::fromStringList(mAuxVariables);
    json_specs["parameters"]       = QJsonArray::fromStringList(mParameters);
    json_specs["model_mo_path"]    = mFilePath;
    json_specs["model_name"]       = mModelName;
    // Initialize JSON doc from JSON object
    QJsonDocument json_specs_doc(json_specs);

    return json_specs_doc;
}
