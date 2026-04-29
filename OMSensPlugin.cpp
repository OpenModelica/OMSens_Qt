/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-2026, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF AGPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.8.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES
 * RECIPIENT'S ACCEPTANCE OF THE OSMC PUBLIC LICENSE OR THE GNU AGPL
 * VERSION 3, ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the OSMC (Open Source Modelica Consortium)
 * Public License (OSMC-PL) are obtained from OSMC, either from the above
 * address, from the URLs:
 * http://www.openmodelica.org or
 * https://github.com/OpenModelica/ or
 * http://www.ida.liu.se/projects/OpenModelica,
 * and in the OpenModelica distribution.
 *
 * GNU AGPL version 3 is obtained from:
 * https://www.gnu.org/licenses/licenses.html#GPL
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */

#include "OMSensPlugin.h"
#include "OMSensDialog.h"
#include "omedit_plugin/model.h"

QString OMSensPlugin::OpenModelicaHome = "";
QString OMSensPlugin::tempPath = "";
QString OMSensPlugin::OMSensBackendPath = "";
QString OMSensPlugin::pythonExecPath = "";

void OMSensPlugin::setOpenModelicaHome(const QString &omhome)
{
  OMSensPlugin::OpenModelicaHome = omhome;
}

void OMSensPlugin::setTempPath(const QString &path)
{
  OMSensPlugin::tempPath = path;
}

void OMSensPlugin::setOMSensPath(const QString &path)
{
  OMSensPlugin::OMSensBackendPath = path;
}

void OMSensPlugin::setPython(const QString &path)
{
  OMSensPlugin::pythonExecPath = path;
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
