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
#include "dialogs/help/HelpBrowser.h"


OMSensDialog::OMSensDialog(Model model, QWidget *parent) : QDialog(parent), mModel(model)
{
    // Dialog settings
    setMinimumWidth(400);
    setWindowTitle("OMSens");

    // OMSens python backend path
    mOMSensPath = "/home/omsens/Documents/OMSens/" ;
    // Python executable path
    mPythonBinPath = "/home/omsens/anaconda3/bin/python";

    // Initialize paths
    mpOMSensPathLabel = new QLabel("OMSens python backend folder:");
    mpOMSensPathValue = new QLabel(mOMSensPath);
    mpOMSensPathValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mpOMSensPathBrowseButton = new QPushButton("Browse");
    mpOMSensPathBrowseButton->setAutoDefault(true);
    mpOMSensPathBrowseButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpOMSensPathBrowseButton, SIGNAL(clicked()), this, SLOT(launchOMSensBackendChooseFolderDialog()));

    mpPythonBinLabel = new QLabel("Python executable:");
    mpPythonBinValue = new QLabel(mPythonBinPath);
    mpPythonBinValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mpPythonBinBrowseButton = new QPushButton("Browse");
    mpPythonBinBrowseButton->setAutoDefault(true);
    mpPythonBinBrowseButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpPythonBinBrowseButton, SIGNAL(clicked()), this, SLOT(launchPythonBinChooseFolderDialog()));

    // Division between paths and buttons
    mpHorizontalLineOne= new QFrame;
    mpHorizontalLineOne->setFrameShape(QFrame::HLine);
    mpHorizontalLineOne->setFrameShadow(QFrame::Sunken);


    // Initialize features
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

    // Division between features and help
    mpHorizontalLineTwo= new QFrame;
    mpHorizontalLineTwo->setFrameShape(QFrame::HLine);
    mpHorizontalLineTwo->setFrameShadow(QFrame::Sunken);

    mpHelpButton = new QPushButton(tr("Help"));
    mpHelpButton->setAutoDefault(true);
    mpHelpButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpHelpButton, SIGNAL(clicked()), SLOT(helpDialog()));

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    // OMSens folder
    mainLayout->addWidget(mpOMSensPathLabel, 0, Qt::AlignLeft);
    QHBoxLayout *pOMSensValueLayout = new QHBoxLayout;
    pOMSensValueLayout->addWidget(mpOMSensPathValue);
    pOMSensValueLayout->addWidget(mpOMSensPathBrowseButton);
    mainLayout->addLayout(pOMSensValueLayout);
    // Python bin
    mainLayout->addWidget(mpPythonBinLabel, 0, Qt::AlignLeft);
    QHBoxLayout *pPythonBinValueLayout = new QHBoxLayout;
    pPythonBinValueLayout->addWidget(mpPythonBinValue);
    pPythonBinValueLayout->addWidget(mpPythonBinBrowseButton);
    mainLayout->addLayout(pPythonBinValueLayout);
    // Division
    mainLayout->addWidget(mpHorizontalLineOne);
    // Buttons
    mainLayout->addWidget(mpIndivButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(mpSweepButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(mpVectButton , 0, Qt::AlignCenter);
    mainLayout->addWidget(mpHorizontalLineTwo);
    mainLayout->addWidget(mpHelpButton , 0, Qt::AlignCenter);
    mainLayout->setAlignment(Qt::AlignCenter);
    setLayout(mainLayout);
}

void OMSensDialog::runIndivSensAnalysis()
{
  QString scriptFileName = "individual_sens_calculator.py" ;
  RunType runType = Individual;
  // Hide this dialog before opening the new one
  runOMSensFeature(runType, scriptFileName);

 // RUN PREDEFINED EXP. NEEDS TO BE ADAPTED
//          // Initialize the Dialog with a predefined analysis
//          // Read JSON with W3 specs
//          QString jsonSpecsName = "exp_01_paper_fig_2_heatmap.json";
//          QString experimentsFolderPath = "/home/omsens/Documents/OMSens/resource/experiments/individual/";
//          QString jsonSpecsPath = QDir::cleanPath(experimentsFolderPath + QDir::separator() + jsonSpecsName);
//          // Reed analysis specifications from disk
//          QString fileContents;
//          QFile file(jsonSpecsPath);
//          file.open(QIODevice::ReadOnly | QIODevice::Text);
//          fileContents = file.readAll();
//          file.close();
//          // Initialize Qt JSON document with file contents
//          QJsonDocument jsonSpecsDocument = QJsonDocument::fromJson(fileContents.toUtf8());
//          // Initialize dialog with JSON specs
//          indivDialog = new IndivParamSensAnalysisDialog(jsonSpecsDocument,this);
//          dialogCodeSecondDialog = indivDialog->exec();;

}
void OMSensDialog::runMultiParameterSweep()
{
  QString scriptFileName = "multiparam_sweep.py" ;
  RunType runType = Sweep;
  // Hide this dialog before opening the new one
  runOMSensFeature(runType, scriptFileName);
}
QJsonDocument OMSensDialog::readJsonFile(QString resultsFolderPath)
{
    QString resultsFileName = "result.json";
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

QString OMSensDialog::progressDialogTextForCurrentTime()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString date = currentTime.toString("dd/MM/yyyy");
    QString h_m_s = currentTime.toString("H:m:s");
    QString scriptRunStartString = "(started on " + date + " at " + h_m_s + ")";
    QString progressDialogText = "Running python script... " + scriptRunStartString;

    return progressDialogText;
}

bool OMSensDialog::runProcessAndShowProgress(QString scriptDirPath, QString command)
{
    QProcess pythonScriptProcess;
    // Set working dir path
    pythonScriptProcess.setWorkingDirectory(scriptDirPath);
    // Initialize dialog showing progress
    QString progressDialogText = progressDialogTextForCurrentTime();
    QProgressDialog *dialog = new QProgressDialog(progressDialogText, "Cancel", 0, 0, this);
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

bool OMSensDialog::defineAndRunCommand(QString scriptDirPath, QString jsonSpecsPath, QString resultsFolderPath, QString scriptPath, QString pythonBinPath)
{
    QString command = commandCallFromPaths(scriptPath, pythonBinPath, jsonSpecsPath, resultsFolderPath);
    bool processEndedCorrectly = runProcessAndShowProgress(scriptDirPath, command);

    return processEndedCorrectly;
}

void OMSensDialog::runOMSensFeature(RunType runType, QString scriptFileName)
{
    // Get script path from OMSens dir and script file name
    QString scriptPath = QDir::cleanPath(mOMSensPath + QDir::separator() + scriptFileName);

    // python executable path from class member
    QString pythonBinPath = mPythonBinPath;

    hide();
    // Initialize and execute dialog
    BaseRunSpecsDialog *runSpecsDialog;
    switch (runType)
    {
        case Vectorial:
           runSpecsDialog = new VectorialSensAnalysisDialog(mModel,this);
           break;
        case Sweep:
           runSpecsDialog = new MultiParamSweepDialog(mModel,this);
           break;
        case Individual:
           runSpecsDialog = new IndivParamSensAnalysisDialog(mModel,this);
           break;
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
        // Write JSON to disk
        QString jsonSpecsPath = writeJsonToDisk(timeStampFolderPath, runSpecifications);
        // Run command
        QString scriptDirPath = dirPathForFilePath(scriptPath);
        bool processEndedCorrectly = defineAndRunCommand(scriptDirPath, jsonSpecsPath, resultsFolderPath, scriptPath, pythonBinPath);
        // If the process ended correctly, show the results dialog
        if (processEndedCorrectly)
        {
            // Read JSON in results folder with the paths to the results of the script
            QJsonDocument jsonPathsDocument = readJsonFile(resultsFolderPath);
            // Initialize results instance with JSON document
            BaseResultsDialog *resultsDialog;
            switch (runType)
            {
                case Vectorial:
                   resultsDialog = new VectorialResultsDialog(jsonPathsDocument, resultsFolderPath, this);
                   break;
                case Sweep:
                   resultsDialog = new SweepResultsDialog(jsonPathsDocument, resultsFolderPath, this);
                   break;
                case Individual:
                   resultsDialog = new IndivSensResultsDialog(jsonPathsDocument, resultsFolderPath, this);
                   break;
            }
            resultsDialog->show();
        }
    }
    // If the user pressed the "Cancel" button, do nothing for now
    if(dialogCode == QDialog::Rejected) {
        // Cancel button clicked
    }
}

void OMSensDialog::runVectorialSensAnalysis()
{
  QString scriptFileName = "vectorial_analysis.py" ;
  RunType runType = Vectorial;
  runOMSensFeature(runType, scriptFileName);
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

void OMSensDialog::launchOMSensBackendChooseFolderDialog()
{
    // Launch dialog
    QString path = QFileDialog::getExistingDirectory(this, tr("Choose Destination Folder"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!path.isEmpty() && !path.isNull())
    {
        // Save path into member variable
        mOMSensPath = path;
        mpOMSensPathValue->setText(mOMSensPath);
    }
}

void OMSensDialog::launchPythonBinChooseFolderDialog()
{
    // Launch dialog
    QString path = QFileDialog::getOpenFileName(this, tr("Choose python interpreter"),
                                                 "/home",
                                                 tr("Python interpreter(*)"));
    if(!path.isEmpty() && !path.isNull())
    {
        // Save path into member variable
        mPythonBinPath = path;
        mpPythonBinValue->setText(mPythonBinPath);
    }
}

void OMSensDialog::helpDialog()
{
    HelpBrowser::showPage(helpTextPath);
}
