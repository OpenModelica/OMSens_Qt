#ifndef OMSENSDIALOG_H
#define OMSENSDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include "model.h"

// Enum so we can refactor the run and results dialog common behaviour between the types of runs
enum RunType {Individual, Sweep, Vectorial};

class OMSensDialog : public QDialog
{
    Q_OBJECT
public:
    OMSensDialog(Model model, QWidget *parent = nullptr);

    QJsonDocument readJsonFile(QString resultsFolderPath);
    
    bool runProcessAndShowProgress(QString scriptDirPath, QString command);
    
    QString createTimestampDir(QString destFolderPath);
    
    QString writeJsonToDisk(QString timeStampFolderPath, QJsonDocument runSpecifications);
    
    QString createResultsFolder(QString timeStampFolderPath);
    
    QString dirPathForFilePath(QString scriptPath);
    
    QString commandCallFromPaths(QString scriptPath, QString pythonBinPath, QString jsonSpecsPath, QString resultsFolderPath);
    
    bool defineAndRunCommand(QString scriptDirPath, QString jsonSpecsPath, QString resultsFolderPath, QString scriptPath, QString pythonBinPath);
    
    void runOMSensFeature(RunType runType, QString scriptFileName);
    
    QString progressDialogTextForCurrentTime();

private:
    // Data
    Model mModel;
    QString mOMSensPath;
    QString mPythonBinPath;
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
    QPushButton *mpHelpButton;
    // Conventions
    QString helpTextPath = "qrc:/OMSens/help/help.html";
    // Auxs

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
};

#endif // OMSENSDIALOG_H
