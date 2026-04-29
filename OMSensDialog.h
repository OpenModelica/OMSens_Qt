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

#ifndef OMSENSDIALOG_H
#define OMSENSDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include "dialogs/BaseRunSpecsDialog.h"
#include "dialogs/indiv/IndivParamSensAnalysisDialog.h"
#include "dialogs/sweep/MultiParamSweepDialog.h"
#include "dialogs/vect/VectorialParamSensAnalysisDialog.h"
#include "dialogs/BaseResultsDialog.h"

// Enum so we can pseudo-reference classes
enum RunType {Individual, Sweep, Vectorial};

class OMSensDialog : public QDialog
{
  Q_OBJECT
public:
  // Constructors
  OMSensDialog(Model model, QWidget *parent = 0);
  // Conventions
  QString helpTextPath                    = "qrc:/OMSens/help/help.html";
  QString exp_specs_file_name             = "experiment_specs.json";
  QString model_specs_file_name           = "model_info.json";
  QString analysis_results_info_file_name = "result.json";
private:
  // Data
  Model mActiveModel;
  QString mOMSensPath;
  QString mPythonBinPath;
  // Dialogs
  VectorialSensAnalysisDialog  *mpVectSensDialog;
  MultiParamSweepDialog        *mpSweepDialog;
  IndivParamSensAnalysisDialog *mpIndivSensDialog;
  // GUI
  QLabel      *mpOMSensPathLabel;
  QLabel      *mpOMSensPathValue;
  QPushButton *mpOMSensPathBrowseButton;
  QLabel      *mpPythonBinLabel;
  QLabel      *mpPythonBinValue;
  QPushButton *mpPythonBinBrowseButton;
  QFrame      *mpHorizontalLineOne;
  QPushButton *mpIndivButton;
  QPushButton *mpSweepButton;
  QPushButton *mpVectButton;
  QFrame      *mpHorizontalLineTwo;
  QPushButton *mpHelpButton; // Not shown for now
  QPushButton *mpLoadExperimentButton;
  // Auxs
  QJsonDocument readJsonFile(QString analysisResultsJSONPath);
  bool runProcessAndShowProgress(QString scriptDirPath, QString command, QStringList args, QString resultsFolderPath);
  QString createTimestampDir(QString destFolderPath);
  QString writeJsonToDisk(QString file_path, QJsonDocument runSpecifications);
  QString createResultsFolder(QString timeStampFolderPath);
  QString dirPathForFilePath(QString scriptPath);
  bool defineAndRunCommand(QString scriptDirPath, QString jsonSpecsPath, QString resultsFolderPath, QString scriptPath, QString pythonBinPath);
  QString progressDialogTextForCurrentTime();
  void runAnalysisAndShowResult(BaseRunSpecsDialog *runSpecsDialog, RunType runType, Model model);
  BaseResultsDialog* showResultsDialog(RunType runType, QString resultsFolderPath);

signals:

public slots:
  void runIndivSensAnalysis();
  void runMultiParameterSweep();
  void runVectorialSensAnalysis();
  void openSensAnalysisResult();
  void openSensAnalysisImage();
  void launchOMSensBackendChooseFolderDialog();
  void launchPythonBinChooseFolderDialog();
  void helpDialog();
  void loadExperimentFileDialog();
};

#endif // OMSENSDIALOG_H
