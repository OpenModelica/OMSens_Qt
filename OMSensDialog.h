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


  QString omsensBackendPath();

  QString pythonExecPath();

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
