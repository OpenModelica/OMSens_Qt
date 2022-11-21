#include "OMSensDialog.h"
#include <QProcess>
#include <QProgressDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QDateTime>
#include <QTextStream>
#include <QMessageBox>
#include <QGuiApplication>

#include "OMSensPlugin.h"
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
#include "specs/IndivSpecs.h"
#include "specs/SweepSpecs.h"
#include "specs/VectSpecs.h"

QString osName()
{
#if defined(Q_OS_ANDROID)
  return QLatin1String("android");
#elif defined(Q_OS_BLACKBERRY)
  return QLatin1String("blackberry");
#elif defined(Q_OS_IOS)
  return QLatin1String("ios");
#elif defined(Q_OS_MACOS)
  return QLatin1String("macos");
#elif defined(Q_OS_TVOS)
  return QLatin1String("tvos");
#elif defined(Q_OS_WATCHOS)
  return QLatin1String("watchos");
#elif defined(Q_OS_WINCE)
  return QLatin1String("wince");
#elif defined(Q_OS_WIN)
  return QLatin1String("windows");
#elif defined(Q_OS_LINUX)
  return QLatin1String("linux");
#elif defined(Q_OS_UNIX)
  return QLatin1String("unix");
#else
  return QLatin1String("unknown");
#endif
}



QString OMSensDialog::omsensBackendPath()
{
  // Get environment var value
  QString envVarVal = qgetenv("OMSENSBACKEND");
  // Check if it's empty
  QString backendPath;
  if(envVarVal.size() == 0)
  {
    backendPath = "?";
  }
  else
  {
    backendPath=envVarVal;
  }
  return backendPath;
}

QString OMSensDialog::pythonExecPath()
{
  QString system = osName();
  QProcess sysProcc;

  // Call command depending on platform
  if (system == "linux") {
    sysProcc.start("which", {"python"});
  } else if (system == "windows") {
    sysProcc.start("where", {"python"});
  } else {
    return "";
  }

  sysProcc.waitForFinished(); // sets current thread to sleep and waits for pingProcess end
  // Check that it's was a sucessful call
  int retCode = sysProcc.exitCode();
  // Define python path
  QString pythonPath;
  if (retCode == 0)
  {
    // Get STDOUT
    QString sysCallSTDOUT(sysProcc.readAllStandardOutput());
    // Sanitize output
    QStringList paths = sysCallSTDOUT.split("\n");
    QString firstPath = paths.at(0);
    pythonPath = firstPath;
  }
  else
  {
    pythonPath = "?";
  }
  return pythonPath.trimmed();
}

OMSensDialog::OMSensDialog(Model model, QWidget *parent) : QDialog(parent), mActiveModel(model)
{
  // Dialog settings
  setMinimumWidth(400);
  setWindowTitle("OMSens");

  helpTextPath                    = "qrc:/OMSens/help/help.html";
  exp_specs_file_name             = "experiment_specs.json";
  model_specs_file_name           = "model_info.json";
  analysis_results_info_file_name = "result.json";

  // OMSens python backend path
  mOMSensPath    = QDir::cleanPath(OMSensPlugin::OpenModelicaHome + "/share/OMSens")/*omsensBackendPath()*/;
  // Python executable path
  mPythonBinPath = QDir::cleanPath(pythonExecPath());
  // Initialize dialogs
  mpVectSensDialog     = new VectorialSensAnalysisDialog(mActiveModel,this);
  mpSweepDialog        = new MultiParamSweepDialog(mActiveModel,this);
  mpIndivSensDialog    = new IndivParamSensAnalysisDialog(mActiveModel,this);
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

  mpSweepButton = new QPushButton(tr("Multi-parameter Sweep"));
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

  // Help (not shown for now)
  mpHelpButton = new QPushButton(tr("Help"));
  mpHelpButton->setAutoDefault(true);
  mpHelpButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
  connect(mpHelpButton, SIGNAL(clicked()), SLOT(helpDialog()));

  // Load experiment
  mpLoadExperimentButton = new QPushButton(tr("Load"));
  mpLoadExperimentButton->setAutoDefault(true);
  mpLoadExperimentButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
  connect(mpLoadExperimentButton, SIGNAL(clicked()), SLOT(loadExperimentFileDialog()));

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
  // Don't show the help for now
  //    mainLayout->addWidget(mpHelpButton , 0, Qt::AlignCenter);
  mainLayout->addWidget(mpLoadExperimentButton , 0, Qt::AlignLeft);

  // Layout settings
  mainLayout->setAlignment(Qt::AlignCenter);
  setLayout(mainLayout);
}


void OMSensDialog::runIndivSensAnalysis()
{
  RunType runType = Individual;
  runAnalysisAndShowResult(mpIndivSensDialog, runType, mActiveModel);
}
void OMSensDialog::runMultiParameterSweep()
{
  RunType runType = Sweep;
  runAnalysisAndShowResult(mpSweepDialog, runType, mActiveModel);
}
void OMSensDialog::runVectorialSensAnalysis()
{
  RunType runType = Vectorial;
  runAnalysisAndShowResult(mpVectSensDialog, runType, mActiveModel);
}

QJsonDocument OMSensDialog::readJsonFile(QString analysisResultsJSONPath)
{
  // Read JSON file into string
  QString val;
  QFile jsonPathsQFile;
  jsonPathsQFile.setFileName(analysisResultsJSONPath);
  if (jsonPathsQFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    val = jsonPathsQFile.readAll();
    jsonPathsQFile.close();
  }
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

bool OMSensDialog::runProcessAndShowProgress(QString scriptDirPath, QString command, QStringList args, QString resultsFolderPath)
{
  QProcess pythonScriptProcess;
  // Set working dir path
  pythonScriptProcess.setWorkingDirectory(scriptDirPath);
  pythonScriptProcess.setProcessChannelMode(QProcess::MergedChannels);
  // Initialize dialog showing progress
  QString progressDialogText = progressDialogTextForCurrentTime();
  QProgressDialog *dialog = new QProgressDialog(progressDialogText, "Cancel", 0, 0, this);
  dialog->setAttribute(Qt::WA_DeleteOnClose);
  // Connect command "close" with dialog close
  connect(&pythonScriptProcess, SIGNAL(finished(int)), dialog, SLOT(close()));
  // Connect dialog "cancel"  with command kill
  connect(dialog, SIGNAL(canceled()), &pythonScriptProcess, SLOT(kill()));

  // Start process
  pythonScriptProcess.start(command, args);
  if (pythonScriptProcess.state() == QProcess::Running) {
    // Show dialog with progress
    dialog->exec();
  } else {
    dialog->close();
  }
  // Wait for the process to finish in the case that we cancel the process and it doesn't have time to finish correctly
  pythonScriptProcess.waitForFinished(3000);
  //
  // See if the process ended correctly
  QProcess::ExitStatus exitStatus = pythonScriptProcess.exitStatus();
  int exitCode = pythonScriptProcess.exitCode();
  // Prepare python call log
  QString python_call_output(pythonScriptProcess.readAll());
  QString python_log_full_str = QString("full command:%1\n\n%2\n\n%3").arg(command, pythonScriptProcess.errorString(), python_call_output);
  // Write log to file
  QString python_log_file_name = "python_log.txt";
  QString python_log_file_path = QDir::cleanPath(resultsFolderPath + QDir::separator() + python_log_file_name);
  QFile logFile(python_log_file_path);
  if ( logFile.open(QIODevice::ReadWrite) )
  {
    QTextStream out(&logFile);
    out << python_log_full_str;
    logFile.close();
  }

  bool processEndedCorrectly = (exitStatus == QProcess::NormalExit) && (exitCode == 0);

  if (!QFile::exists(QDir::cleanPath(resultsFolderPath + QDir::separator() + analysis_results_info_file_name))) {
    QMessageBox::critical(this, QGuiApplication::applicationDisplayName(), python_log_full_str);
  }

  return processEndedCorrectly;
}

QString OMSensDialog::createTimestampDir(QString destFolderPath)
{
  QDateTime currentTime = QDateTime::currentDateTime();
  QString date = currentTime.toString("yyyy-MM-dd");
  QString h_m_s = currentTime.toString("H_m_s");
  QString timeStampFolderPath = QDir::cleanPath(destFolderPath + QDir::separator() + date + QDir::separator() + h_m_s);;
  QDir timestampFolderPathDir(timeStampFolderPath);
  if (!timestampFolderPathDir.exists()){
    timestampFolderPathDir.mkpath(".");
  }

  return timeStampFolderPath;
}

QString OMSensDialog::writeJsonToDisk(QString file_path, QJsonDocument runSpecificationsDoc)
{
  // Save analysis specifications to disk
  QFile runSpecificationsFile(file_path);
  if ( runSpecificationsFile.open(QIODevice::ReadWrite) )
  {
    runSpecificationsFile.write(runSpecificationsDoc.toJson());
    runSpecificationsFile.close();
  }

  return file_path;
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

bool OMSensDialog::defineAndRunCommand(QString scriptDirPath, QString jsonSpecsPath, QString resultsFolderPath, QString scriptPath, QString pythonBinPath)
{
  // Define command
  QStringList args = {scriptPath, jsonSpecsPath, "--dest_folder_path", resultsFolderPath};
  // Call process
  bool processEndedCorrectly = runProcessAndShowProgress(scriptDirPath, pythonBinPath, args, resultsFolderPath);

  return processEndedCorrectly;
}

BaseResultsDialog* OMSensDialog::showResultsDialog(RunType runType, QString resultsFolderPath)
{
  QString analysisResultsJSONPath = QDir::cleanPath(resultsFolderPath + QDir::separator() + analysis_results_info_file_name);
  QJsonDocument jsonPathsDocument = readJsonFile(analysisResultsJSONPath);
  // Initialize results instance with JSON document
  BaseResultsDialog *resultsDialog = 0;
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
  return resultsDialog;
}

void OMSensDialog::runAnalysisAndShowResult(BaseRunSpecsDialog *runSpecsDialog, RunType runType, Model model)
{
  // Hide this dialog before opening the new one
  this->hide();
  int dialogCode  = runSpecsDialog->exec();
  // If the dialog was accepted by the user, run the analysis
  BaseResultsDialog* resultDialog = 0;
  if(dialogCode == QDialog::Accepted)
  {
    // Get script path from OMSens dir and script file name
    QString scriptFileName = runSpecsDialog->pythonScriptName();
    QString scriptPath = QDir::cleanPath(mOMSensPath + QDir::separator() + scriptFileName);
    // python executable path from class member
    QString pythonBinPath = mPythonBinPath;

    QJsonDocument exp_specs = runSpecsDialog->getRunSpecifications();
    QString destFolderPath = runSpecsDialog->getDestFolderPath();
    // Make timestamp subfolder in dest folder path
    QString timeStampFolderPath = createTimestampDir(destFolderPath);
    // Make sub-folder where the results will be written
    QString resultsFolderPath = createResultsFolder(timeStampFolderPath);
    // Write Exp specs to disk
    QString exp_specs_path = QDir::cleanPath(timeStampFolderPath + QDir::separator() + exp_specs_file_name);
    writeJsonToDisk(exp_specs_path, exp_specs);
    // Write model specs to disk
    QString model_specs_path = QDir::cleanPath(timeStampFolderPath + QDir::separator() + model_specs_file_name);
    QJsonDocument model_specs = model.toJson();
    writeJsonToDisk(model_specs_path, model_specs);
    // Run command
    QString scriptDirPath = dirPathForFilePath(scriptPath);
    bool processEndedCorrectly = defineAndRunCommand(scriptDirPath, exp_specs_path, resultsFolderPath, scriptPath, pythonBinPath);
    // If the process ended correctly, show the results dialog
    if (processEndedCorrectly) {
      // Read JSON in results folder with the paths to the results of the script
      resultDialog = showResultsDialog(runType, resultsFolderPath);
    }
  }
  // If the user pressed the "Cancel" button, do nothing for now
  if(dialogCode == QDialog::Rejected) {
    // Cancel button clicked
  }

  // First show OMSens main dialog
  this->show();

  if(resultDialog)
  {
    // If a result dialog was initialized, show it
    resultDialog->show();
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
  HelpBrowser *helpBrowser = new HelpBrowser(helpTextPath);
  helpBrowser->show();
}


void OMSensDialog::loadExperimentFileDialog()
{
  // Launch
  QString exp_specs_path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "/home",
                                                        tr("Experiments (*.json)"));
  if(!exp_specs_path.isEmpty() && !exp_specs_path.isNull())
  {
    // Load file
    QJsonDocument json_specs_doc = readJsonFile(exp_specs_path);
    // Get object from top
    QJsonObject json_specs = json_specs_doc.object();
    // Check if contains key specifying analysis type
    QString analysis_type_key = "analysis_type";
    if(json_specs.contains(analysis_type_key))
    {
      // Get analysis type
      QString analysis_type = json_specs.value(QString(analysis_type_key)).toString();
      // Find the corresponding analysis type
      BaseRunSpecsDialog *runSpecsDialog = 0;
      RunType             runType = Individual;
      // Get specs file folder path
      QFileInfo exp_specs_file_info = QFileInfo(exp_specs_path);
      QDir exp_specs_dir = exp_specs_file_info.absoluteDir();
      // We assume that the model information is available in the same folder as the experiment specifications
      QString model_specs_path = QDir::cleanPath(exp_specs_dir.absolutePath() + QDir::separator() + model_specs_file_name);
      // Read model info from file
      QJsonDocument model_info_json = readJsonFile(model_specs_path);
      Model               model = Model(model_info_json);
      if (analysis_type == IndivSpecs::analysis_id_str)
      {
        IndivSpecs runSpecs = IndivSpecs(json_specs_doc);
        runSpecsDialog = new IndivParamSensAnalysisDialog(model, runSpecs, this);
        runType = Individual;

      }
      else if (analysis_type == SweepSpecs::analysis_id_str)
      {
        SweepSpecs runSpecs = SweepSpecs(json_specs_doc);
        runSpecsDialog = new MultiParamSweepDialog(model, runSpecs, this);
        runType = Sweep;
      }
      else if (analysis_type == VectSpecs::analysis_id_str)
      {
        VectSpecs runSpecs = VectSpecs(json_specs_doc);
        runSpecsDialog = new VectorialSensAnalysisDialog(model, runSpecs, this);
        runType = Vectorial;
      }

      runAnalysisAndShowResult(runSpecsDialog,runType,model);
    }
  }
}
