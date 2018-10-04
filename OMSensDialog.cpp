#include "OMSensDialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include "OMSens/model.h"
#include "OMSens/dialogs/indiv/IndivSensAnalTypeDialog.h"
#include "OMSens/dialogs/indiv/IndivParamSensAnalysisDialog.h"
#include "OMSens/dialogs/indiv/IndivSensResultsDialog.h"
#include "OMSens/dialogs/sweep/MultiParamSweepDialog.h"
#include "OMSens/dialogs/sweep/SweepResultDialog.h"
#include "OMSens/dialogs/vect/VectorialParamSensAnalysisDialog.h"
#include "OMSens/dialogs/vect/VectorialResultsDialog.h"
#include "OMSens/dialogs/general/ImageViewerDialog.h"
#include "OMSens/dialogs/general/CSVViewerDialog.h"
#include "Modeling/ModelWidgetContainer.h"

OMSensDialog::OMSensDialog(ModelWidget* currentModelWidget, QWidget *parent) : QDialog(parent)
{
    // Save args
    mpCurrentModelWidget = currentModelWidget;

    // Dialog settings
    setMinimumWidth(400);
    setWindowTitle("OMSens");

    // Initialize buttons
    mpIndivButton = new QPushButton(tr("Individual Parameter Based Sensitivity Analysis"), this);
    mpIndivButton->setAutoDefault(true);
    mpIndivButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpIndivButton, SIGNAL(clicked()), SLOT(runIndivSensAnalysis()));

    mpSweepButton = new QPushButton(tr("Multi-parameter sweep"), this);
    mpSweepButton->setAutoDefault(true);
    mpSweepButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpSweepButton, SIGNAL(clicked()), SLOT(runMultiParameterSweep()));

    mpVectButton = new QPushButton(tr("Vectorial Parameter Based Sensitivity Analysis"), this);
    mpVectButton->setAutoDefault(true);
    mpVectButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpVectButton, SIGNAL(clicked()), SLOT(runVectorialSensAnalysis()));

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(mpIndivButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(mpSweepButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(mpVectButton , 0, Qt::AlignCenter);
    mainLayout->setAlignment(Qt::AlignCenter);
    setLayout(mainLayout);
}

Model OMSensDialog::currentModelOpen()
{
    // Get the ModelWidget instance for the model currently open
    // Create OMSens Model from ModelWidget information. The following code should be moved in the future to a Model
    //  constructor
// Model meta data
    QString filePath = mpCurrentModelWidget->getLibraryTreeItem()->getFileName();
    QString modelName = mpCurrentModelWidget->getLibraryTreeItem()->getNameStructure();
    // Model data
    // Get components to get the Model information
    QList<Component*>  pModelComponents = mpCurrentModelWidget->getDiagramGraphicsView()->getComponentsList();
//    foreach (Component* component, pModelComponents) {
//        ComponentInfo *componentInfo = component->getComponentInfo();
//        QString componentDefinedInClass = mpCurrentModelWidget->getLibraryTreeItem()->getNameStructure();
//        QString value = componentInfo->getParameterValue(mpOMCProxy, componentDefinedInClass);
//        std:cout << componentInfo->getVariablity().toUtf8().constData() << " " << componentInfo->getClassName().toUtf8().constData()  << " " << componentInfo->getName().toUtf8().constData() << " = " << value.toUtf8().constData() << "'" << componentInfo->getComment().toUtf8().constData() << "'" << std::endl;
//    }
    // Variable input Real continua:
    //   getVariability() == ""
    //   getCausality() == "input"
    //   getClassName() == "Real"
    QList<QString> inputVariables1 = getComponentsMatching(pModelComponents, "", "input", "Real");
    // Variable input Real continua usando output y Real:
    //   getVariability() == ""
    //   getCausality() == "input"
    //   getClassName() == "Modelica.Blocks.Interfaces.RealInput"
    QList<QString> inputVariables2 = getComponentsMatching(pModelComponents, "", "input", "Modelica.Blocks.Interfaces.RealInput");
    // Variable output Real continua usando output y Real:
    //   getVariability() == ""
    //   getCausality() == "output
    //   getClassName() == "Real"
    QList<QString> outputVariables1 =getComponentsMatching(pModelComponents, "", "output", "Real");
    // Variable output Real continua usando Modelica blocks interfaces:
    //   getVariability() == ""
    //   getCausality() == "output
    //   getClassName() == "Modelica.Blocks.Interfaces.RealOutput"
    QList<QString> outputVariables2 =getComponentsMatching(pModelComponents, "", "output", "Modelica.Blocks.Interfaces.RealOutput");
    // Variable aux Real continua:
    //   getVariability() == ""
    //   getCausality() == ""
    //   getClassName() == "Real"
    QList<QString> auxVariables =getComponentsMatching(pModelComponents, "", "", "Real");
    // Parameter Real :
    //   getVariability() == "parameter"
    //   getCausality() == ""
    //   getClassName() == "Real"
    QList<QString> parameters = getComponentsMatching(pModelComponents, "parameter", "", "Real");
    // Join output variables
    QList<QString> outputVariables = outputVariables1 + outputVariables2;
    // Join input variables
    QList<QString> inputVariables = inputVariables1 + inputVariables2;
    Model model(inputVariables, outputVariables, auxVariables, parameters, filePath, modelName);

    return model;
}

bool OMSensDialog::checkIfActiveModel()
{
    bool isThereAnActiveModel = mpCurrentModelWidget != 0;
    return isThereAnActiveModel;
}

void OMSensDialog::runIndivSensAnalysis()
{
  // Hide this dialog before opening the new one
  hide();
  // Check if there's an active model in the OMEdit editor
  bool isThereAnActiveModel = checkIfActiveModel();
  Model *pModel; // Needs to be added to the heap
  IndivSensAnalTypeDialog *analysisTypeDialog; // needs to be extracted from the "if" and freed at the end of the function
  if(isThereAnActiveModel){
      // Get the OMSens model from the OMEdit information abount the open model
      Model model = currentModelOpen();
      pModel = &model;
      analysisTypeDialog = new IndivSensAnalTypeDialog(pModel,this);
  }
  else
  {
      // There's not an active model so initialize the pointer with 0
      pModel = 0;
      analysisTypeDialog = new IndivSensAnalTypeDialog(pModel,this);
  }
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
          QString experimentsFolderPath = "/home/omsens/Documents/omsens/resource/experiments/individual/";
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
          // Quickfix: get the current model again for now so we don't have to store it in the heap
          Model model = currentModelOpen();

          // Ask the user for analysis specifications
          indivDialog = new IndivParamSensAnalysisDialog(model,this);
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
          QString indivAnalysisScriptPath = "/home/omsens/Documents/omsens/individual_sens_calculator.py" ;
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
          qWarning() << val;
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
  // Close OMSens dialog
  accept();
}
void OMSensDialog::runMultiParameterSweep()
{
  // Hide this dialog before opening the new one
  hide();
  // Check if there's an active model in the OMEdit editor
  bool isThereAnActiveModel = checkIfActiveModel();
  if(isThereAnActiveModel){
      // Get the OMSens model from the OMEdit information abount the open model
      Model model = currentModelOpen();
      MultiParamSweepDialog *sweepDialog = new MultiParamSweepDialog(model,this);
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
          QString scriptPath = "/home/omsens/Documents/omsens/multiparam_sweep.py" ;
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
  // Close OMSens dialog
  accept();
}
void OMSensDialog::runVectorialSensAnalysis()
{
  // Hide this dialog before opening the new one
  hide();
  // Check if there's an active model in the OMEdit editor
  bool isThereAnActiveModel = checkIfActiveModel();
  if(isThereAnActiveModel){
      // Get the OMSens model from the OMEdit information abount the open model
      Model model = currentModelOpen();
      VectorialSensAnalysisDialog *vectDialog = new VectorialSensAnalysisDialog(model,this);
      int dialogCode  = vectDialog->exec();
      if(dialogCode == QDialog::Accepted)
      {   // Get user inputs from dialog
          QJsonObject runSpecifications = vectDialog->getRunSpecifications();
          QString destFolderPath = vectDialog->getDestFolderPath();
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
          // Run vectorial analysis
          QString scriptPath = "/home/omsens/Documents/omsens/vectorial_analysis.py" ;
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
          // Initialize results instance with JSON document
          VectorialResultsDialog *resultsDialog = new VectorialResultsDialog(jsonPathsDocument,this);
          resultsDialog->show();
      }
      // If the user pressed the "Cancel" button, do nothing for now
      if(dialogCode == QDialog::Rejected) {
          // Cancel button clicked
      }
   }
  // Close OMSens dialog
  accept();
}
void OMSensDialog::runPythonScript()
{
//ADAPTAR:
QString filePath;
filePath = QFileDialog::getOpenFileName(this,tr("Open Python Script"), "", tr("Python script(*.py)"));
QString pythonBinPath = "/home/adanos/anaconda3/bin/python";
QString command = QString(pythonBinPath) + " " + filePath;
QFileInfo fileNameFileInfo = QFileInfo(filePath);
QDir      fileDir          = fileNameFileInfo.canonicalPath();
QString fileDirPath        = fileDir.canonicalPath();
bool currentDirChangeSuccessful = QDir::setCurrent(fileDirPath);
if (currentDirChangeSuccessful)
{
    system(qPrintable(command));
}
//ADAPTAR^
}
void OMSensDialog::runCURVITestFile()
{
	// BORRAR ESTA FUNCION

	// VIEJO!
//    QString testFilePath = QFileDialog::getOpenFileName(this,tr("Open Vectorial Sensitivity Script"), "", tr("Vectorial Sensitivity script(*.txt)"));
//    QString curviSensOutputPath = QString("/tmp/vectorialSensOutput_omedit.csv");
//    // Ofi
//    //QString curviSensBinPath = "/home/adanos/Documents/repos/tesis-work/modelica_scripts/fortran/curvi";
//    // Casa
//    QString curviSensBinPath = "/home/adanos/Documents/TPs/tesis/repos/modelica_scripts/fortran/curvi";
//    QString command = QString(curviSensBinPath) + " " + testFilePath + " " + curviSensOutputPath;
//    QFileInfo curviSensFileInfo = QFileInfo(curviSensBinPath);
//    QDir      fileDir          = curviSensFileInfo.canonicalPath();
//    QString fileDirPath        = fileDir.canonicalPath();
//    bool currentDirChangeSuccessful = QDir::setCurrent(fileDirPath);
//    if (currentDirChangeSuccessful)
//    {
//        system(qPrintable(command));
//    }
}
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


QList<QString> OMSensDialog::getComponentsMatching(QList<Component*> pModelComponents, const char *variability, const char *causality, const char *className)
{
    QList<QString> componentNames;
    foreach (Component* component, pModelComponents) {
        ComponentInfo *componentInfo = component->getComponentInfo();
        QString componentVariability = componentInfo->getVariablity();
        QString componentCausality   = componentInfo->getCausality();
        QString componentClassName   = componentInfo->getClassName();
        if(componentVariability == variability && componentCausality ==causality && componentClassName == className )
        {
            componentNames.append(componentInfo->getName());
        }
    }
    return componentNames;
}
