#include "IndivParamSensAnalysisDialog.h"

#include <QMessageBox>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>
#include <QJsonArray>
#include <QJsonDocument>

#include "model.h"
#include "tabs/VariablesTab.h"
#include "tabs/ParametersSimpleTab.h"
#include "tabs/SimulationTab.h"
#include "tabs/HelpTab.h"

IndivParamSensAnalysisDialog::IndivParamSensAnalysisDialog(QJsonDocument jsonSpecsDocument, QWidget *pParent)
  : QDialog(pParent)
{
    // Get main object from document
    QJsonObject jsonSpecs = jsonSpecsDocument.object();
    // Get straightforward specs
    QString modelName     = jsonSpecs.value(QString("model_name")).toString();
    QString modelFilePath = jsonSpecs.value(QString("model_mo_path")).toString();
    double percentage     = jsonSpecs.value(QString("percentage")).toDouble();
    double startTime      = jsonSpecs.value(QString("start_time")).toDouble();
    double stopTime       = jsonSpecs.value(QString("stop_time")).toDouble();
    // Get variables QVariant list
    QList<QVariant> variablesQVariant = jsonSpecs.value(QString("vars_to_analyze")).toArray().toVariantList();
    // Transform from list of QVariant to list of QString
    QList<QString> variables = fromListOfVariantToListOfStr(variablesQVariant);
    // Get parameters QVariant list
    QList<QVariant> parametersQVariant = jsonSpecs.value(QString("parameters_to_perturb")).toArray().toVariantList();
    // Transform from list of QVariant to list of QString
    QList<QString> parameters = fromListOfVariantToListOfStr(parametersQVariant);
    // Call the initializer with the parsed data from the JSON specs
    initializeDialogWithData(variables, parameters, modelName, modelFilePath, percentage, startTime, stopTime);
}

IndivParamSensAnalysisDialog::IndivParamSensAnalysisDialog(Model model, QWidget *pParent)
  : QDialog(pParent)
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
    mpSimulationSettingsTab = new SimulationTab(modelName, modelFilePath, startTime, stopTime, defaultResultsFolderPath);
    mpVariablesTab          = new VariablesTab(variables);
    mpParametersTab         = new ParametersSimpleTab(parameters, percentage);
    mpHelpTab               = new HelpTab(helpText);

    // Initialize tabs container widget
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpSimulationSettingsTab , tr("Simulation"));
    mpTabWidget->addTab(mpVariablesTab          , tr("Variables"));
    mpTabWidget->addTab(mpParametersTab         , tr("Parameters"));
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

QJsonObject IndivParamSensAnalysisDialog::getRunSpecifications() const
{
    return mRunSpecifications;
}

QString IndivParamSensAnalysisDialog::getDestFolderPath() const
{
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


void IndivParamSensAnalysisDialog::runIndivParamSensAnalysis()
{
    // Instantiate members that will be read by the caller of this dialog
    // Instantiate dest folder path from user input
    destFolderPath = mpSimulationSettingsTab->getDestFolderPath();
    // Modify json with the data entered in this dialog
    // Model info
    mRunSpecifications["model_name"]      = mpSimulationSettingsTab->getModelName();
    mRunSpecifications["model_mo_path"]   = mpSimulationSettingsTab->getModelPath();
    // User inputs info
    // Variables to analyze
    QJsonArray varsToAnalize;
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
    mRunSpecifications["vars_to_analyze"] = varsToAnalize;

    mRunSpecifications["start_time"] = mpSimulationSettingsTab->getStartTimeValue();
    mRunSpecifications["stop_time"]  = mpSimulationSettingsTab->getStopTimeValue();
    mRunSpecifications["percentage"] = mpParametersTab->getPercentageValue();
    // Parameters to perturb
    QJsonArray parametersToPerturb;
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
    mRunSpecifications["parameters_to_perturb"] = parametersToPerturb;
    accept();
}


QString IndivParamSensAnalysisDialog::readHelpText()
{
    // Temp version that has the text hardcoded
    QString helpText = "<p><strong>Individual Sensitivity Analysis</strong></p>"
                "<p>Perturbs parameters individually, one at a time and by the same percentage.</p>"
                "<p>This type of analysis is useful to find to which parameters a variable of the model is most sensitive to.</p>"
                "<p>The number of simulations will be equal to the number of parameters to analyze plus one, the simulation corresponding to the standard run.</p>"
                "<p><strong>Known limitations</strong></p>"
                "<p>Only parameters and variables of type Real are recognized. Not even renamings of the sort of 'type MyType = Real' are supported.</p>"
                "<p>Arrays of any type are not supported either.</p>";
    // TEMP VERSION ^

    // VERSION THAT READS FROM FILE:
    // // Make QFile from class member variable
    // QFile helpTextFile(helpTextPath);
    // // Read file into variable
    // QString helpText;
    // if (helpTextFile.open(QFile::ReadOnly | QFile::Text))
    // {
    //     QTextStream in(&helpTextFile);
    //     helpText = in.readAll();
    //     helpTextFile.close();
    // }
    // VERSION THAT READS FROM FILE^

    return helpText;
}
