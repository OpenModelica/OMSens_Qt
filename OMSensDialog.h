#ifndef OMSENSDIALOG_H
#define OMSENSDIALOG_H

#include <QWidget>
#include <QDialog>
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
    
    QString writeJsonToDisk(QString timeStampFolderPath, QJsonObject runSpecifications);
    
    QString createResultsFolder(QString timeStampFolderPath);
    
    QString dirPathForFilePath(QString scriptPath);
    
    QString commandCallFromPaths(QString scriptPath, QString pythonBinPath, QString jsonSpecsPath, QString resultsFolderPath);
    
    bool defineAndRunCommand(QString jsonSpecsPath, QString scriptPath, QString pythonBinPath, QString scriptDirPath, QString resultsFolderPath);
    
    bool defineAndRunCommand(QString timeStampFolderPath, QString scriptDirPath, QJsonObject runSpecifications, QString resultsFolderPath, QString scriptPath, QString pythonBinPath);
    
    void runOMSensFeature(RunType runType, QString scriptPath);
    
private:
    // Data
    Model mModel;
    // GUI
    QPushButton *mpIndivButton;
    QPushButton *mpSweepButton;
    QPushButton *mpVectButton;
    // Auxs

signals:

public slots:
  void runIndivSensAnalysis();
  void runMultiParameterSweep();
  void runVectorialSensAnalysis();
  void openSensAnalysisResult();
  void openSensAnalysisImage();
};

#endif // OMSENSDIALOG_H
