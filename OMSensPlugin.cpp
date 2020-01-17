#include "OMSensPlugin.h"
#include "OMSensDialog.h"
#include "omedit_plugin/model.h"

QString OMSensPlugin::OpenModelicaHome = "";
QString OMSensPlugin::tempPath = "";

void OMSensPlugin::setOpenModelicaHome(const QString &omhome)
{
  OMSensPlugin::OpenModelicaHome = omhome;
}

void OMSensPlugin::setTempPath(const QString &path)
{
  OMSensPlugin::tempPath = path;
}

void OMSensPlugin::analyzeModel(const QList<QVariant> &modelData)
{
  // Create a QJsonDocument from the model data.
  // Initialize JSON root object
  QJsonObject jsonObject;
  jsonObject["input_variables"] = modelData.size() > 0 ? QJsonArray::fromStringList(modelData.at(0).toStringList()) : QJsonArray::fromStringList(QStringList());
  jsonObject["output_variables"] = modelData.size() > 1 ? QJsonArray::fromStringList(modelData.at(1).toStringList()) : QJsonArray::fromStringList(QStringList());
  jsonObject["aux_variables"] = modelData.size() > 2 ? QJsonArray::fromStringList(modelData.at(2).toStringList()) : QJsonArray::fromStringList(QStringList());
  jsonObject["parameters"] = modelData.size() > 3 ? QJsonArray::fromStringList(modelData.at(3).toStringList()) : QJsonArray::fromStringList(QStringList());
  jsonObject["model_mo_path"] = modelData.size() > 4 ? modelData.at(4).toString() : QString("");
  jsonObject["model_name"] = modelData.size() > 5 ? modelData.at(5).toString() : QString("");

  // Initialize main dialog with model
  OMSensDialog* pOmsensDialog =  new OMSensDialog(Model(QJsonDocument(jsonObject)));
  // Show dialog
  pOmsensDialog->show();
}
