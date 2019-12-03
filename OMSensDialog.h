#ifndef OMSENSDIALOG_H
#define OMSENSDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include "omedit_plugin/model.h"
#include "dialogs/BaseRunSpecsDialog.h"
#include "dialogs/indiv/IndivParamSensAnalysisDialog.h"
#include "dialogs/sweep/MultiParamSweepDialog.h"
#include "dialogs/vect/VectorialParamSensAnalysisDialog.h"
#include "dialogs/BaseResultsDialog.h"
#include <QProgressDialog>
#include <QProgressBar>
#include <QProcess>


// Enum so we can pseudo-reference classes
enum RunType {Individual, Sweep, Vectorial};

class OMSensDialog : public QDialog
{
    Q_OBJECT
public:
    // Constructors
    OMSensDialog(Model model, QWidget *parent = nullptr);
    // Conventions
    QString helpTextPath                    = "qrc:/OMSens/help/help.html";
    QString exp_specs_file_name             = "experiment_specs.json";
    QString model_specs_file_name           = "model_info.json";
    QString analysis_results_info_file_name = "result.json";


private:
    // Data
    Model mActiveModel;
    QProcess pythonScriptProcess;

    QString mOMSensPath;
    QString mPythonBinPath;
    QString mOMSensResultsPath;

    // Dialogs
    VectorialSensAnalysisDialog  *mpVectSensDialog;
    MultiParamSweepDialog        *mpSweepDialog;
    IndivParamSensAnalysisDialog *mpIndivSensDialog;

    QProgressBar *q_progress_bar;
    QProgressDialog *q_progress_dialog;

    // GUI   
    QLabel      *mpOMSensPathLabel;
    QLabel      *mpOMSensPathValue;
    QPushButton *mpOMSensPathBrowseButton;
    QLabel      *mpPythonBinLabel;
    QLabel      *mpPythonBinValue;
    QPushButton *mpPythonBinBrowseButton;
    QFrame      *mpHorizontalLineOne;

    QPushButton *mpIndivButton; QPushButton *mpIndivButtonAnalysis;
    QPushButton *mpSweepButton; QPushButton *mpSweepButtonAnalysis;
    QPushButton *mpVectButton; QPushButton *mpVectButtonAnalysis;
    QPushButton *mpConstrainedButton; QPushButton *mpConstrainedButtonAnalysis;

    QFrame      *mpHorizontalLineTwo;
    QPushButton *mpHelpButton; // Not shown for now
    QPushButton *mpLoadExperimentButton;
    QPushButton *mpLoadExperimentButton2;
    QPushButton *mpLoadExperimentButton3;
    QPushButton *mpLoadExperimentButton4;

    // Auxs
    QJsonDocument readJsonFile(QString analysisResultsJSONPath);
    bool runProcessAndShowProgress(QString scriptDirPath, QString command);
    QString createTimestampDir(QString destFolderPath);
    QString writeJsonToDisk(QString file_path, QJsonDocument runSpecifications);
    QString createResultsFolder(QString timeStampFolderPath);
    QString dirPathForFilePath(QString scriptPath);
    QString commandCallFromPaths(QString scriptPath, QString pythonBinPath, QString jsonSpecsPath, QString resultsFolderPath);
    bool defineAndRunCommand(QString scriptDirPath, QString jsonSpecsPath, QString resultsFolderPath, QString scriptPath, QString pythonBinPath);
    QString progressDialogTextForCurrentTime();

    void runAnalysisAndShowResult(BaseRunSpecsDialog *runSpecsDialog, RunType runType, Model model);
    BaseResultsDialog* showResultsDialog(RunType runType, QString resultsFolderPath);

    void showSpecificAnalysis(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, RunType runType);


signals:

public slots:
  void readOut();
  void readErr();

  // RUN AND SHOW ANALYSIS
  void runIndivSensAnalysis();
  void runMultiParameterSweep();
  void runVectorialSensAnalysis();

  // SHOW ANALYSIS
  void showMultiParameterSweepAnalysis();
  void showVectorialSensAnalysis();
  void showIndivSensAnalysis();

  void openSensAnalysisResult();
  void openSensAnalysisImage();
  void launchOMSensBackendChooseFolderDialog();
  void launchPythonBinChooseFolderDialog();
  void helpDialog();
  void loadExperimentFileDialog();
};

#endif // OMSENSDIALOG_H
