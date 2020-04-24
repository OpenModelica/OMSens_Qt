#include "OMSensDialog.h"
#include <QProcess>
#include <QProgressDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QDateTime>
#include "omedit_plugin/model.h"
#include "dialogs/indiv/IndivSensAnalTypeDialog.h"
#include "dialogs/indiv/IndivParamSensAnalysisDialog.h"
#include "dialogs/indiv/IndivSensResultsDialog.h"

#include "dialogs/sweep/MultiParamSweepDialog.h"
#include "dialogs/sweep/SweepResultDialog.h"
#include "dialogs/sweep/PlotFromDataDialog.h"

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
#include <QMessageBox>
#include <QTimer>
#include <string>


OMSensDialog::OMSensDialog(Model model, QWidget *parent) : QDialog(parent), mActiveModel(model)
{
    // Dialog settings
    setMinimumWidth(600);
    setWindowTitle("OMSens");

    // OMSens python backend path
    mPythonBinPath      = "/home/omsens/anaconda3/bin/python";
    mOMSensPath         = "/home/omsens/Documents/OMSens/";
    mOMSensResultsPath  = "/home/omsens/Documents/results_experiments/";

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

    // Individual parameters
    mpIndivButton = new QPushButton(tr("Run new"));
    mpIndivButton->setAutoDefault(true);
    mpIndivButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpIndivButton, SIGNAL(clicked()), SLOT(runIndivSensAnalysis()));
    mpIndivButtonAnalysis = new QPushButton(tr("Analyze Results"));
    mpIndivButtonAnalysis->setEnabled(false);
    connect(mpIndivButtonAnalysis, SIGNAL(clicked()), SLOT(showIndivSensAnalysis()));

    // Parameter Sweep
    mpSweepButton = new QPushButton(tr("Run new"));
    mpSweepButton->setAutoDefault(true);
    mpSweepButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpSweepButton, SIGNAL(clicked()), SLOT(runMultiParameterSweep()));
    mpSweepButtonAnalysis = new QPushButton(tr("Analyze Results"));
    connect(mpSweepButtonAnalysis, SIGNAL(clicked()), SLOT(showMultiParameterSweepAnalysis()));

    // Vectorial
    mpVectButton = new QPushButton(tr("Run new"));
    mpVectButton->setAutoDefault(true);
    mpVectButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpVectButton, SIGNAL(clicked()), SLOT(runVectorialSensAnalysis()));
    mpVectButtonAnalysis = new QPushButton(tr("Analyze Results"));
    mpVectButtonAnalysis->setEnabled(false);
    connect(mpVectButtonAnalysis, SIGNAL(clicked()), SLOT(showVectorialSensAnalysis()));

    // Constrained (TODO: do connections the right way)
    mpConstrainedButton = new QPushButton(tr("Run new"));
    mpConstrainedButton->setAutoDefault(true);
    mpConstrainedButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(mpConstrainedButton, SIGNAL(clicked()), SLOT(runVectorialSensAnalysis()));
    mpConstrainedButton->setEnabled(false);

    mpConstrainedButtonAnalysis = new QPushButton(tr("Analyze Results"));
    mpConstrainedButtonAnalysis->setEnabled(false);
    connect(mpConstrainedButtonAnalysis, SIGNAL(clicked()), SLOT(showVectorialSensAnalysis()));


    // Division between features and help
    mpHorizontalLineTwo= new QFrame;
    mpHorizontalLineTwo->setFrameShape(QFrame::HLine);
    mpHorizontalLineTwo->setFrameShadow(QFrame::Sunken);

    // Help (not shown for now)
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
    // LOAD EXPERIMENT PARAMETERIZATION
    mpLoadExperimentButton = new QPushButton(tr("Load previous"));
    mpLoadExperimentButton->setAutoDefault(true);
    mpLoadExperimentButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpLoadExperimentButton, SIGNAL(clicked()), SLOT(loadExperimentFileDialog()));

    mpLoadExperimentButton2 = new QPushButton(tr("Load previous"));
    mpLoadExperimentButton2->setAutoDefault(true);
    mpLoadExperimentButton2->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpLoadExperimentButton2, SIGNAL(clicked()), SLOT(loadExperimentFileDialog()));

    mpLoadExperimentButton3 = new QPushButton(tr("Load previous"));
    mpLoadExperimentButton3->setAutoDefault(true);
    mpLoadExperimentButton3->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpLoadExperimentButton3, SIGNAL(clicked()), SLOT(loadExperimentFileDialog()));

    mpLoadExperimentButton4 = new QPushButton(tr("Load previous"));
    mpLoadExperimentButton4->setAutoDefault(true);
    mpLoadExperimentButton4->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpLoadExperimentButton4, SIGNAL(clicked()), SLOT(loadExperimentFileDialog()));
    mpLoadExperimentButton4->setEnabled(false);

    // LABEL 1
    QLabel *label1 = new QLabel("Individual Parameter Based Sensitivity ");
    mainLayout->addWidget(label1, 0, Qt::AlignLeft);
    QHBoxLayout *row1 = new QHBoxLayout;
    row1->addWidget(mpIndivButton);
    row1->addWidget(mpIndivButtonAnalysis);
    row1->addWidget(mpLoadExperimentButton);
    mainLayout->addItem(row1);

    // LABEL 2
    QLabel *label2 = new QLabel("Multi-parameter Sweep");
    mainLayout->addWidget(label2, 0, Qt::AlignLeft);
    QHBoxLayout *row2 = new QHBoxLayout;
    row2->addWidget(mpSweepButton);
    row2->addWidget(mpSweepButtonAnalysis);
    row2->addWidget(mpLoadExperimentButton2);
    mainLayout->addItem(row2);

    // LABEL 3
    QLabel *label3 = new QLabel("Vectorial Parameter Based Sensitivity Analysis");
    mainLayout->addWidget(label3, 0, Qt::AlignLeft);
    QHBoxLayout *row3 = new QHBoxLayout;
    row3->addWidget(mpVectButton);
    row3->addWidget(mpVectButtonAnalysis);
    row3->addWidget(mpLoadExperimentButton3);
    mainLayout->addItem(row3);

    // LABEL 4
    QLabel *label4 = new QLabel("Constrained Interval Parameter Based Sensitivity Analysis");
    mainLayout->addWidget(label4, 0, Qt::AlignLeft);
    QHBoxLayout *row4 = new QHBoxLayout;
    row4->addWidget(mpConstrainedButton);
    row4->addWidget(mpConstrainedButtonAnalysis);
    row4->addWidget(mpLoadExperimentButton4);
    mainLayout->addItem(row4);

    // Layout settings
    mainLayout->setAlignment(Qt::AlignCenter);
    setLayout(mainLayout);
}

// RUN ANALYSIS AND SHOW RESULTS
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

// SHOW RESULTS OF (PREVIOUS) ANALYSIS
void OMSensDialog::showIndivSensAnalysis()
{
    RunType runType = Individual;
    showSpecificAnalysis(mPythonBinPath, mOMSensPath, mOMSensResultsPath, runType);
}
void OMSensDialog::showMultiParameterSweepAnalysis()
{
    RunType runType = Sweep;
    showSpecificAnalysis(mPythonBinPath, mOMSensPath, mOMSensResultsPath, runType);
}
void OMSensDialog::showVectorialSensAnalysis()
{
    RunType runType = Vectorial;
    showSpecificAnalysis(mPythonBinPath, mOMSensPath, mOMSensResultsPath, runType);
}

QJsonDocument OMSensDialog::readJsonFile(QString analysisResultsJSONPath)
{
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
    // Set working dir path
    pythonScriptProcess.setWorkingDirectory(scriptDirPath);

    // Initialize dialog showing progress
    QString progressDialogText = progressDialogTextForCurrentTime();
    q_progress_dialog = new QProgressDialog(progressDialogText, "Cancel", 0, 100, this);
    q_progress_dialog->setAttribute(Qt::WA_DeleteOnClose);

    this->setWindowModality(Qt::NonModal);
    q_progress_dialog->setWindowModality(Qt::NonModal);

    // Connect command "close" with dialog close
    connect(&pythonScriptProcess, SIGNAL(finished(int)), q_progress_dialog, SLOT(close()));
    connect(&pythonScriptProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readOut()));
    connect(q_progress_dialog, SIGNAL(canceled()), &pythonScriptProcess, SLOT(kill()));

    // Added
    pythonScriptProcess.setEnvironment(QProcess::systemEnvironment());
    pythonScriptProcess.setProcessChannelMode(QProcess::MergedChannels);

    // Start process
    pythonScriptProcess.start(command);
    q_progress_dialog->exec();

    // Wait for the process to finish in the case that we cancel the process and it doesn't have time to finish correctly
    pythonScriptProcess.waitForFinished(3000);

    QProcess::ExitStatus exitStatus = pythonScriptProcess.exitStatus();
    int exitCode = pythonScriptProcess.exitCode();
    bool processEndedCorrectly = (exitStatus == QProcess::NormalExit) && (exitCode == 0);

    // Show output after proccess ended
    if (!processEndedCorrectly) {
        QString output_string(pythonScriptProcess.readAllStandardOutput());
        QMessageBox msg;
        msg.setText(output_string);
        msg.exec();
    }

    return processEndedCorrectly;
}

void OMSensDialog::readOut()
{
    QString output_string(pythonScriptProcess.readAllStandardOutput());
    int val = 0;
    if (output_string != "") {
        try {
            std::string last_element = output_string.split(",").back().toStdString();
            last_element.erase(last_element.begin(),
                               std::find_if(last_element.begin(), last_element.end(),
                                            std::bind1st(std::not_equal_to<char>(), ',')));
            val = std::stoi(last_element);
            q_progress_dialog->setValue(val);
        } catch (int e) {
            QMessageBox msg;
            msg.setText("ERROR");
            msg.exec();
        }
    }
}

void OMSensDialog::readErr()
{

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
    QString resultsFolderPath = QDir::cleanPath(timeStampFolderPath + QDir::separator() + "results");
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

bool OMSensDialog::defineAndRunCommand(QString scriptDirPath, QString jsonSpecsPath, QString resultsFolderPath,
                                       QString scriptPath, QString pythonBinPath)
{
    QString command = pythonBinPath + " " + scriptPath;
    command += " " + jsonSpecsPath + " --dest_folder_path " + resultsFolderPath;

    bool processEndedCorrectly = runProcessAndShowProgress(scriptDirPath, command);
    return processEndedCorrectly;
}

BaseResultsDialog* OMSensDialog::showResultsDialog(RunType runType, QString resultsFolderPath)
{
    QString analysisResultsJSONPath = QDir::cleanPath(resultsFolderPath + QDir::separator() + analysis_results_info_file_name);
    QJsonDocument jsonPathsDocument = readJsonFile(analysisResultsJSONPath);
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

void OMSensDialog::showSpecificAnalysis(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, RunType runType)
{
    BaseResultsDialog *resultsDialog = 0;

    switch (runType)
    {
        case Vectorial:
            resultsDialog = new PlotFromDataDialog(mPythonBinPath, mOMSensPath, mOMSensResultsPath, this);
            break;
        case Sweep:
            resultsDialog = new PlotFromDataDialog(mPythonBinPath, mOMSensPath, mOMSensResultsPath, this);
            break;
        case Individual:
            resultsDialog = new PlotFromDataDialog(mPythonBinPath, mOMSensPath, mOMSensResultsPath, this);
            break;
    }
    if(resultsDialog) {
        resultsDialog->show();
    }
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
        QString scriptPath = runSpecsDialog->mPythonScriptPath;
        QString scriptDirPath = runSpecsDialog->mPythonScriptLibraryPath;

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
        // MODIFY HERE
        // TODO: change folder results path passed to python process
        bool processEndedCorrectly = defineAndRunCommand(scriptDirPath, exp_specs_path,
                                                         timeStampFolderPath, scriptPath, pythonBinPath);

        // If the process ended correctly, show the results dialog
        if (processEndedCorrectly)
        {
            // Read JSON in results folder with the paths to the results of the script
            resultDialog = showResultsDialog(runType, resultsFolderPath);
        } else {

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
            BaseRunSpecsDialog *runSpecsDialog;
            RunType             runType;
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
