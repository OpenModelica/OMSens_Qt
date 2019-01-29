#include "IndivParamSensAnalysisDialog.h"

#include <QMessageBox>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>

#include "../../model.h"
#include "../../tabs/VariablesTab.h"
#include "../../tabs/ParametersSimpleTab.h"
#include "../../tabs/SimulationTab.h"
#include "../../tabs/HelpTab.h"

// Conventions
QString IndivParamSensAnalysisDialog::pythonScriptName()
{
    return "individual_sens_calculator.py";
}

// Constructor
IndivParamSensAnalysisDialog::IndivParamSensAnalysisDialog(IndivSpecs runSpecs, QWidget *pParent)
  : BaseRunSpecsDialog(pParent)
{
    // Get straightforward specs
    QString modelName      = runSpecs.model_name;
    QString modelFilePath  = runSpecs.model_file_path;
    double percentage      = runSpecs.percentage;
    double startTime       = runSpecs.start_time;
    double stopTime        = runSpecs.stop_time;
    QStringList variables  = runSpecs.vars_to_analyze;
    QStringList parameters = runSpecs.parameters_to_perturb;

    // Call the initializer with the parsed data from the specs
    initializeDialogWithData(variables, parameters, modelName, modelFilePath, percentage, startTime, stopTime);
}

IndivParamSensAnalysisDialog::IndivParamSensAnalysisDialog(Model model, QWidget *pParent)
  : BaseRunSpecsDialog(pParent)
{
    // Get Model information necessary for the dialog
    QList<QString> variables  = model.getAuxVariables()+model.getOutputVariables();
    QList<QString> parameters = model.getParameters();
    QString modelName         = model.getModelName();
    QString modelFilePath     = model.getFilePath();

    // Default settings
    double percentage = 5;
    double startTime  = 0;
    double stopTime   = 1;

    // Initialize the dialog with this info
    initializeDialogWithData(variables, parameters, modelName, modelFilePath, percentage, startTime, stopTime);
}

void IndivParamSensAnalysisDialog::initializeDialogWithData(QList<QString> variables, QList<QString> parameters, QString modelName, QString modelFilePath, double percentage, double startTime, double stopTime)
{
    // Help text description
    QString helpText = readHelpText();
    // Initialize tabs
    QString defaultResultsFolderPath = "/home/omsens/Documents/indiv_sens_results";
    QString parametersQuickExplanation = "Each selected parameter is perturbed in isolation, one at a time";
    mpSimulationSettingsTab = new SimulationTab(modelName, modelFilePath, startTime, stopTime, defaultResultsFolderPath);
    mpVariablesTab          = new VariablesTab(variables);
    mpParametersTab         = new ParametersSimpleTab(parameters, parametersQuickExplanation);
    mpHelpTab               = new HelpTab(helpText);
    mpPerturbationTab       = new PerturbationTab(percentage);

    // Initialize tabs container widget
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpSimulationSettingsTab , tr("Simulation"));
    mpTabWidget->addTab(mpVariablesTab          , tr("Variables"));
    mpTabWidget->addTab(mpParametersTab         , tr("Parameters"));
    mpTabWidget->addTab(mpPerturbationTab       , tr("Perturbation"));
    mpTabWidget->addTab(mpHelpTab               , tr("Help"));

    //Buttons
    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("Run Analysis", QDialogButtonBox::AcceptRole);
    mpButtonBox->addButton("Cancel"      , QDialogButtonBox::RejectRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &IndivParamSensAnalysisDialog::runIndivParamSensAnalysis);
    connect(mpButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    // Dialog settings
    setWindowTitle("Run Individual Sensitivity Analysis");
    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mpTabWidget);
    mainLayout->addWidget(mpButtonBox);
    setLayout(mainLayout);
}

QJsonDocument IndivParamSensAnalysisDialog::getRunSpecifications() const
{
    // Initialize specs from dialog info
    IndivSpecs runSpecs = IndivSpecs(
        mpSimulationSettingsTab->getModelPath(),
        mpSimulationSettingsTab->getModelName(),
        this->getParametersToPerturb(),
        mpPerturbationTab->getPerturbationValue(),
        mpSimulationSettingsTab->getStartTimeValue(),
        mpSimulationSettingsTab->getStopTimeValue(),
        this->getVarsToAnalize()
    );
    // It's easier to just return the json doc (concrete class) instead of returning a RunSpecifications (abstract class)
    //   and having to deal with pointers
    QJsonDocument runSpecsDoc = runSpecs.toJson();
    return runSpecsDoc;
}

QString IndivParamSensAnalysisDialog::getDestFolderPath() const
{
    QString destFolderPath = mpSimulationSettingsTab->getDestFolderPath();
    return destFolderPath;
}

// Auxs
QList<QString> IndivParamSensAnalysisDialog::fromListOfVariantToListOfStr(QList<QVariant> listOfQVariant)
{
    QList<QString> listOfStr;
    foreach (QVariant objQVariant, listOfQVariant) {
        QString objStr = objQVariant.toString();
        listOfStr.append(objStr);
    }
    return listOfStr;
}


QStringList IndivParamSensAnalysisDialog::getVarsToAnalize() const
{
    QStringList varsToAnalize;
    QTableWidget *pVarsTable = mpVariablesTab->getVariablesTable();
    for(int i_row = 0; i_row < pVarsTable->rowCount(); i_row++)
    {
        // Get boolean value if include or not
        const int includeCBoxPos = VariablesTab::cboxColPos;
        QCheckBox *includeCBox= qobject_cast<QCheckBox *>(pVarsTable->cellWidget(i_row,includeCBoxPos));
        bool include_or_not_var = includeCBox->isChecked();

        if(include_or_not_var)
        {
            // If the user included this var, add it to the list
            // Get variable name
            const int varColPos = VariablesTab::varColPos;
            QLabel *varNameLabel= qobject_cast<QLabel *>(pVarsTable->cellWidget(i_row,varColPos));
            QString varNameStr = varNameLabel->text();
            // Add it to the list
            varsToAnalize.append(varNameStr);
        }
    }

    return varsToAnalize;
}

QStringList IndivParamSensAnalysisDialog::getParametersToPerturb() const
{
    QStringList parametersToPerturb;
    QTableWidget *pParamsTable = mpParametersTab->getParametersTable();
    for(int i_row = 0; i_row < pParamsTable->rowCount(); i_row++)
    {
        // Get boolean value if include or not
        const int perturbCBoxPos = mpParametersTab->cboxColPos;
        QCheckBox *perturbCBox= qobject_cast<QCheckBox *>(pParamsTable->cellWidget(i_row,perturbCBoxPos));
        bool perturb_or_not_param = perturbCBox->isChecked();

        if(perturb_or_not_param)
        {
            // If the user included this param, add it to the list
            // Get param name
            const int paramColPos = mpParametersTab->paramColPos;
            QLabel *paramNameLabel= qobject_cast<QLabel *>(pParamsTable->cellWidget(i_row,paramColPos));
            QString paramNameStr = paramNameLabel->text();
            // Add it to the list
            parametersToPerturb.append(paramNameStr);
        }
    }

    return parametersToPerturb;
}

void IndivParamSensAnalysisDialog::runIndivParamSensAnalysis()
{
    // Just accept for now
    accept();
}


QString IndivParamSensAnalysisDialog::readHelpText()
{
    // Make QFile from class member variable
    QFile helpTextFile(helpTextPath);
    // Read file into variable
    QString helpText;
    if (helpTextFile.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&helpTextFile);
        helpText = in.readAll();
        helpTextFile.close();
    }

    return helpText;
}
