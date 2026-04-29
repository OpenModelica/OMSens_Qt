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

#include "OMSensDialog.h"
#include "omedit_plugin/model.h"

#include <QApplication>
#include <QTemporaryDir>


// Model example to be used when OMSens is used as standalone
// (main function below example)
Model modelExample()
{
  // Define model data
  const QList<QString> inputVariables;
  const QList<QString> parameters( QList<QString>()
                                   << "realParam1"
                                   << "realParam2"
                                   << "realParam3");
  const QList<QString> outputVariables( QList<QString>()
                                   << "outvar1"
                                   << "outvar2"
                                   << "outvar3");
  const QList<QString> auxVariables;

  // Model name
  QString modelName = "ModelWithVariousParams";
  // Model path in Qt resources
  QString fileResourcePath = ":/OMSens/ModelWithVariousParams.mo";
  // Model file name to be used when written to disk
  QString tempModelName = "ModelWithVariousParams.mo";
  // Temp dir where to write Model
  QTemporaryDir tempDir;
  // Disable auto remove so the user can check the model
  tempDir.setAutoRemove(false);
  QString  filePath=  QDir::cleanPath(tempDir.path() + QDir::separator() + tempModelName);
  if (tempDir.isValid()) {
    QFile::copy(fileResourcePath, filePath);
  }
  // Initialize model
  Model model(inputVariables, outputVariables, auxVariables, parameters, filePath, modelName);

  return model;
}

int main(int argc, char *argv[])
{
    // Initialize Qt Application
    QApplication a(argc, argv);
    // Model information for testing:
    Model model = modelExample();
    // Initialize OMSens Dialog
    OMSensDialog dialog(model);
    // Show OMSens Dialog
    dialog.show();
    // Run and end Qt Application
    return a.exec();
}
