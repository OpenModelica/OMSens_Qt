#include "OMSensDialog.h"
#include <QProcess>
#include <QProgressDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QDateTime>
#include "model.h"
#include "dialogs/indiv/IndivSensAnalTypeDialog.h"
#include "dialogs/indiv/IndivParamSensAnalysisDialog.h"
#include "dialogs/indiv/IndivSensResultsDialog.h"
#include "dialogs/sweep/MultiParamSweepDialog.h"
#include "dialogs/sweep/SweepResultDialog.h"
#include "dialogs/vect/VectorialParamSensAnalysisDialog.h"
#include "dialogs/vect/VectorialResultsDialog.h"
#include "dialogs/general/ImageViewerDialog.h"
#include "dialogs/general/CSVViewerDialog.h"
#include "dialogs/BaseRunSpecsDialog.h"
#include "dialogs/BaseResultsDialog.h"

// Enum so we can refactor the run and results dialog common behaviour between the types of runs
enum RunType {Individual, Sweep, Vectorial};

OMSensDialog::OMSensDialog(Model model, QWidget *parent) : QDialog(parent), mModel(model)
{
    // Dialog settings
    setMinimumWidth(400);
    setWindowTitle("OMSens");

    // Initialize buttons
    mpIndivButton = new QPushButton(tr("Individual Parameter Based Sensitivity Analysis"));
    mpIndivButton->setAutoDefault(true);
    mpIndivButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpIndivButton, SIGNAL(clicked()), SLOT(runIndivSensAnalysis()));

    mpSweepButton = new QPushButton(tr("Multi-parameter sweep"));
    mpSweepButton->setAutoDefault(true);
    mpSweepButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpSweepButton, SIGNAL(clicked()), SLOT(runMultiParameterSweep()));

    mpVectButton = new QPushButton(tr("Vectorial Parameter Based Sensitivity Analysis"));
    mpVectButton->setAutoDefault(true);
    mpVectButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpVectButton, SIGNAL(clicked()), SLOT(runVectorialSensAnalysis()));

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mpIndivButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(mpSweepButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(mpVectButton , 0, Qt::AlignCenter);
    mainLayout->setAlignment(Qt::AlignCenter);
    setLayout(mainLayout);
}

void OMSensDialog::runIndivSensAnalysis()
{
  // Hide this dialog before opening the new one
  hide();
  IndivSensAnalTypeDialog * analysisTypeDialog = new IndivSensAnalTypeDialog(mModel,this);
  // Ask the user if they want to run a sample or define an analysis by themselves
  int dialogCodeFirstDialog = analysisTypeDialog->exec();
  if(dialogCodeFirstDialog == QDialog::Accepted)
  {
      // The user chose to run some kind of analysis
      bool choseW3InsteadOfOpenModel = analysisTypeDialog->choseW3InsteadOfOpenModel;
      IndivParamSensAnalysisDialog *indivDialog;
      int dialogCodeSecondDialog;
      if (choseW3InsteadOfOpenModel)
      {
          // Initialize the Dialog with a predefined analysis
          // Read JSON with W3 specs
          QString jsonSpecsName = "exp_01_paper_fig_2_heatmap.json";
          QString experimentsFolderPath = "/home/omsens/Documents/OMSens/resource/experiments/individual/";
          QString jsonSpecsPath = QDir::cleanPath(experimentsFolderPath + QDir::separator() + jsonSpecsName);
          // Reed analysis specifications from disk
          QString fileContents;
          QFile file(jsonSpecsPath);
          file.open(QIODevice::ReadOnly | QIODevice::Text);
          fileContents = file.readAll();
          file.close();
          // Initialize Qt JSON document with file contents
          QJsonDocument jsonSpecsDocument = QJsonDocument::fromJson(fileContents.toUtf8());
          // Initialize dialog with JSON specs
          indivDialog = new IndivParamSensAnalysisDialog(jsonSpecsDocument,this);
          dialogCodeSecondDialog = indivDialog->exec();;
      }
      else
      {
          // Give the user the option to run an analysis from the current model active
          // Ask the user for analysis specifications
          indivDialog = new IndivParamSensAnalysisDialog(mModel,this);
          dialogCodeSecondDialog = indivDialog->exec();
      }
      // If the user pressed the "Ok" button, get the user inputs
      if(dialogCodeSecondDialog == QDialog::Accepted)
      {   // Get user inputs from dialog
          QJsonObject runSpecifications = indivDialog->getRunSpecifications();
          QString destFolderPath = indivDialog->getDestFolderPath();
          // Make timestamp subfolder in dest folder path
          QDateTime currentTime = QDateTime::currentDateTime();
          QString date = currentTime.toString("dd-MM-yyyy");
          QString h_m_s = currentTime.toString("H_m_s");
          QString timeStampFolderPath = QDir::cleanPath(destFolderPath + QDir::separator() + date + QDir::separator() + h_m_s);;
          QDir timestampFolderPathDir(timeStampFolderPath);
          if (!timestampFolderPathDir.exists()){
            timestampFolderPathDir.mkpath(".");
          }
          // Write JSON to disk
          QString jsonSpecsName = "experiment_specs.json";
          QString jsonSpecsPath = QDir::cleanPath(timeStampFolderPath + QDir::separator() + jsonSpecsName);
          // Save analysis specifications to disk
          QJsonDocument runSpecificationsDoc(runSpecifications);
          QFile runSpecificationsFile(jsonSpecsPath);
          if ( runSpecificationsFile.open(QIODevice::ReadWrite) )
          {
              runSpecificationsFile.write(runSpecificationsDoc.toJson());
              runSpecificationsFile.close();
          }
          // Make sub-folder where the results will be written
          QString resultsFolderPath = QDir::cleanPath(timeStampFolderPath + QDir::separator() + "results");;
          QDir resultsFolderPathDir(resultsFolderPath);
          if (!resultsFolderPathDir.exists()){
            resultsFolderPathDir.mkpath(".");
          }
          // Run individual sens analysis
          QString indivAnalysisScriptPath = "/home/omsens/Documents/OMSens/individual_sens_calculator.py" ;
          QString pythonBinPath = "/home/omsens/anaconda3/bin/python";
          QString scriptDestPathFlag = "--dest_folder_path";
          QString scriptDestPathFlagAndArg = scriptDestPathFlag + " " + resultsFolderPath;
          QString command = pythonBinPath + " " + indivAnalysisScriptPath + " " + jsonSpecsPath + " " + scriptDestPathFlagAndArg;
          QFileInfo fileNameFileInfo = QFileInfo(indivAnalysisScriptPath);
          QDir      fileDir          = fileNameFileInfo.canonicalPath();
          QString fileDirPath        = fileDir.canonicalPath();
          bool currentDirChangeSuccessful = QDir::setCurrent(fileDirPath);
          if (currentDirChangeSuccessful)
          {
              system(qPrintable(command));
          }
          // Read JSON in results folder with the paths to all the matrices, heatmaps, etc
          QString analysisResultsJSONPath = QDir::cleanPath(resultsFolderPath + QDir::separator() + "paths.json");
          // Read JSON file into string
          QString val;
          QFile jsonPathsQFile;
          jsonPathsQFile.setFileName(analysisResultsJSONPath);
          jsonPathsQFile.open(QIODevice::ReadOnly | QIODevice::Text);
          val = jsonPathsQFile.readAll();
          jsonPathsQFile.close();
          // Parse string into json document
          QJsonDocument jsonPathsDocument = QJsonDocument::fromJson(val.toUtf8());
          // Initialize results instance with JSON document
          IndivSensResultsDialog *resultsDialog = new IndivSensResultsDialog(jsonPathsDocument,this);
          resultsDialog->show();
      }
      // If the user pressed the "Cancel" button, do nothing for now
      if(dialogCodeSecondDialog == QDialog::Rejected) {
          // Cancel button clicked
      }

  }
  // If the user pressed the "Cancel" button on the first dialog, do nothing for now
  if(dialogCodeFirstDialog == QDialog::Rejected) {
      // Cancel button clicked
  }
}
void OMSensDialog::runMultiParameterSweep()
{
  // Hide this dialog before opening the new one
  hide();
  // Check if there's an active model in the OMEdit editor
  // Get the OMSens model from the OMEdit information abount the open model
  MultiParamSweepDialog *sweepDialog = new MultiParamSweepDialog(mModel,this);
  int dialogCode  = sweepDialog->exec();
  if(dialogCode == QDialog::Accepted)
  {   // Get user inputs from dialog
      QJsonObject runSpecifications = sweepDialog->getRunSpecifications();
      QString destFolderPath = sweepDialog->getDestFolderPath();
      // Make timestamp subfolder in dest folder path
      QDateTime currentTime = QDateTime::currentDateTime();
      QString date = currentTime.toString("dd-MM-yyyy");
      QString h_m_s = currentTime.toString("H_m_s");
      QString timeStampFolderPath = QDir::cleanPath(destFolderPath + QDir::separator() + date + QDir::separator() + h_m_s);;
      QDir timestampFolderPathDir(timeStampFolderPath);
      if (!timestampFolderPathDir.exists()){
        timestampFolderPathDir.mkpath(".");
      }
      // Write JSON to disk
      QString jsonSpecsName = "experiment_specs.json";
      QString jsonSpecsPath = QDir::cleanPath(timeStampFolderPath + QDir::separator() + jsonSpecsName);
      // Save analysis specifications to disk
      QJsonDocument runSpecificationsDoc(runSpecifications);
      QFile runSpecificationsFile(jsonSpecsPath);
      if ( runSpecificationsFile.open(QIODevice::ReadWrite) )
      {
          runSpecificationsFile.write(runSpecificationsDoc.toJson());
          runSpecificationsFile.close();
      }
      // Make sub-folder where the results will be written
      QString resultsFolderPath = QDir::cleanPath(timeStampFolderPath + QDir::separator() + "results");;
      QDir resultsFolderPathDir(resultsFolderPath);
      if (!resultsFolderPathDir.exists()){
        resultsFolderPathDir.mkpath(".");
      }
      // Run sweep
      QString scriptPath = "/home/omsens/Documents/OMSens/multiparam_sweep.py" ;
      QString pythonBinPath = "/home/omsens/anaconda3/bin/python";
      QString scriptDestPathFlag = "--dest_folder_path";
      QString scriptDestPathFlagAndArg = scriptDestPathFlag + " " + resultsFolderPath;
      QString command = pythonBinPath + " " + scriptPath + " " + jsonSpecsPath + " " + scriptDestPathFlagAndArg;
      QFileInfo scriptFileInfo = QFileInfo(scriptPath);
      QDir      scriptDir          = scriptFileInfo.canonicalPath();
      QString scriptDirPath        = scriptDir.canonicalPath();
      bool currentDirChangeSuccessful = QDir::setCurrent(scriptDirPath);
      if (currentDirChangeSuccessful)
      {
          system(qPrintable(command));
      }
      // Read JSON in results folder with the paths to the results of the script
      QString analysisResultsJSONPath = QDir::cleanPath(resultsFolderPath + QDir::separator() + "paths.json");
      // Read JSON file into string
      QString val;
      QFile jsonPathsQFile;
      jsonPathsQFile.setFileName(analysisResultsJSONPath);
      jsonPathsQFile.open(QIODevice::ReadOnly | QIODevice::Text);
      val = jsonPathsQFile.readAll();
      jsonPathsQFile.close();
      // Parse string into json document
      QJsonDocument jsonPathsDocument = QJsonDocument::fromJson(val.toUtf8());
      // Initialize results instance with JSON document
      SweepResultsDialog *resultsDialog = new SweepResultsDialog(jsonPathsDocument,this);
      resultsDialog->show();
  }
  // If the user pressed the "Cancel" button, do nothing for now
  if(dialogCode == QDialog::Rejected) {
      // Cancel button clicked
  }
}
QJsonDocument OMSensDialog::readJsonFile(QString resultsFolderPath)
{
    QString resultsFileName = "optim_results.json";
    QString analysisResultsJSONPath = QDir::cleanPath(resultsFolderPath + QDir::separator() + resultsFileName);
    // Read JSON file into string
    QString val;
    QFile jsonPathsQFile;
    jsonPathsQFile.setFileName(analysisResultsJSONPath);
    jsonPathsQFile.open(QIODevice::ReadOnly | QIODevice::Text);
    val = jsonPathsQFile.readAll();
    jsonPathsQFile.close();
    // Parse string into json document
    QJsonDocument jsonPathsDocument = QJsonDocument::fromJson(val.toUtf8());

    return jsonPathsDocument;
}

bool OMSensDialog::runProcessAndShowProgress(QString scriptDirPath, QString command)
{
    QProcess pythonScriptProcess;
    // Set working dir path
    pythonScriptProcess.setWorkingDirectory(scriptDirPath);
    // Initialize dialog showing progress
    QProgressDialog *dialog = new QProgressDialog("Running python script...", "Cancel", 0, 0, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    // Connect command "close" with dialog close
    connect(&pythonScriptProcess, SIGNAL(finished(int)), dialog, SLOT(close()));
    // Connect dialog "cancel"  with command kill
    connect(dialog, SIGNAL(canceled()), &pythonScriptProcess, SLOT(kill()));

    // Start process
    pythonScriptProcess.start(command);
    // Show dialog with progress
    dialog->exec();
    // Wait for the process to finish in the case that we cancel the process and it doesn't have time to finish correctly
    pythonScriptProcess.waitForFinished(3000);

    // See if the process ended correctly
    QProcess::ExitStatus exitStatus = pythonScriptProcess.exitStatus();
    int exitCode = pythonScriptProcess.exitCode();

    bool processEndedCorrectly = (exitStatus == QProcess::NormalExit) && (exitCode == 0);

    return processEndedCorrectly;
}

QString OMSensDialog::createTimestampDir(QString destFolderPath)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString date = currentTime.toString("dd-MM-yyyy");
    QString h_m_s = currentTime.toString("H_m_s");
    QString timeStampFolderPath = QDir::cleanPath(destFolderPath + QDir::separator() + date + QDir::separator() + h_m_s);;
    QDir timestampFolderPathDir(timeStampFolderPath);
    if (!timestampFolderPathDir.exists()){
      timestampFolderPathDir.mkpath(".");
    }

    return timeStampFolderPath;
}

QString OMSensDialog::writeJsonToDisk(QString timeStampFolderPath, QJsonObject runSpecifications)
{
    QString jsonSpecsName = "experiment_specs.json";
    QString jsonSpecsPath = QDir::cleanPath(timeStampFolderPath + QDir::separator() + jsonSpecsName);
    // Save analysis specifications to disk
    QJsonDocument runSpecificationsDoc(runSpecifications);
    QFile runSpecificationsFile(jsonSpecsPath);
    if ( runSpecificationsFile.open(QIODevice::ReadWrite) )
    {
        runSpecificationsFile.write(runSpecificationsDoc.toJson());
        runSpecificationsFile.close();
    }

    return jsonSpecsPath;
}

QString OMSensDialog::createResultsFolder(QString timeStampFolderPath)
{
    QString resultsFolderPath = QDir::cleanPath(timeStampFolderPath + QDir::separator() + "results");;
    QDir resultsFolderPathDir(resultsFolderPath);
    if (!resultsFolderPathDir.exists()){
      resultsFolderPathDir.mkpath(".");
    }

    return resultsFolderPath;
}

QString OMSensDialog::dirPathForFilePath(QString scriptPath)
{
    QFileInfo scriptFileInfo = QFileInfo(scriptPath);
    QDir      scriptDir          = scriptFileInfo.canonicalPath();
    QString scriptDirPath        = scriptDir.canonicalPath();

    return scriptDirPath;
}

QString OMSensDialog::commandCallFromPaths(QString scriptPath, QString pythonBinPath, QString jsonSpecsPath, QString resultsFolderPath)
{
    QString scriptDestPathFlag = "--dest_folder_path";
    QString scriptDestPathFlagAndArg = scriptDestPathFlag + " " + resultsFolderPath;
    QString command = pythonBinPath + " " + scriptPath + " " + jsonSpecsPath + " " + scriptDestPathFlagAndArg;

    return command;
}

bool OMSensDialog::defineAndRunCommand(QString timeStampFolderPath, QString scriptDirPath, QJsonObject runSpecifications, QString resultsFolderPath, QString scriptPath, QString pythonBinPath)
{
    QString jsonSpecsPath = writeJsonToDisk(timeStampFolderPath, runSpecifications);
    QString command = commandCallFromPaths(scriptPath, pythonBinPath, jsonSpecsPath, resultsFolderPath);
    bool processEndedCorrectly = runProcessAndShowProgress(scriptDirPath, command);

    return processEndedCorrectly;
}

void OMSensDialog::runVectorialSensAnalysis()
{
  QString scriptPath = "/home/omsens/Documents/OMSens/vectorial_analysis.py" ;
  QString scriptDirPath = dirPathForFilePath(scriptPath);
  QString pythonBinPath = "/home/omsens/anaconda3/bin/python";
  RunType runType = Vectorial;
  // Hide this dialog before opening the new one
  hide();
  // Initialize and execute dialog
  BaseRunSpecsDialog *runSpecsDialog;
  if (runType == Vectorial)
  {
      runSpecsDialog = new VectorialSensAnalysisDialog(mModel,this);
  }
  int dialogCode  = runSpecsDialog->exec();
  // If the dialog was accepted by the user, run the analysis
  if(dialogCode == QDialog::Accepted)
  {   // Get user inputs from dialog
      QJsonObject runSpecifications = runSpecsDialog->getRunSpecifications();
      QString destFolderPath = runSpecsDialog->getDestFolderPath();
      // Make timestamp subfolder in dest folder path
      QString timeStampFolderPath = createTimestampDir(destFolderPath);
      // Make sub-folder where the results will be written
      QString resultsFolderPath = createResultsFolder(timeStampFolderPath);
      // Run command
      bool processEndedCorrectly = defineAndRunCommand(timeStampFolderPath, scriptDirPath, runSpecifications, resultsFolderPath, scriptPath, pythonBinPath);
      // If the process ended correctly, show the results dialog
      if (processEndedCorrectly)
      {
          // Read JSON in results folder with the paths to the results of the script
          QJsonDocument jsonPathsDocument = readJsonFile(resultsFolderPath);
          // Initialize results instance with JSON document
          BaseResultsDialog *resultsDialog;
          if (runType == Vectorial)
          {
              resultsDialog = new VectorialResultsDialog(jsonPathsDocument,this);
          }
          resultsDialog->show();
      }
  }
  // If the user pressed the "Cancel" button, do nothing for now
  if(dialogCode == QDialog::Rejected) {
      // Cancel button clicked
  }
}

// OLD FUNCTIONS THAT HAVE BEEN REPLACED:
void OMSensDialog::openSensAnalysisResult()
{
//ADAPTAR:
 // Ask for file path using dialog
 QString filePath = QFileDialog::getOpenFileName(this,tr("Open Sensitivity Analysis Results"), "", tr("Comma Separated Values file(*.csv)"));
 // Check if the user selected a file or if they clicked cancel
 if (!filePath.isNull()){
     // Initialize Results dialog
     CSVViewerDialog *pSensResult = new CSVViewerDialog(filePath, this);
     pSensResult->exec();
 }
//ADAPTAR^
}
void OMSensDialog::openSensAnalysisImage()
{
//ADAPTAR:
  //Get the valid types supported by the image viewer
   QStringList mimeTypeFilters =ImageViewerDialog::compatibleMIMETypes();
   // Initialize the QFileDialog instance to ask the user for a file
   QFileDialog dialog(this, tr("Open File"));
   dialog.setMimeTypeFilters(mimeTypeFilters);
   dialog.selectMimeTypeFilter("image/png");
   // Ask for file path using dialog
   dialog.exec();
   QString filePath = dialog.selectedFiles().first();

  // Check if the user selected a file or if they clicked cancel
  if (!filePath.isNull()){
      // Initialize Results dialog
      ImageViewerDialog *pImageViewer = new ImageViewerDialog(filePath, this);
      pImageViewer->exec();
  }
  // open sens analysis Image
//ADAPTAR^
}
