#include "MultiParamSweepDialog.h"

#include <QGridLayout>
#include <QHeaderView>
#include <QSizePolicy>
#include <QJsonArray>
#include <QJsonDocument>
#include <QCheckBox>
#include <QTextStream>
#include <QComboBox>

#include "../../model.h"
#include "../../tabs/ParametersExtendedTab.h"
#include "../../tabs/HelpTab.h"

// Conventions
QString MultiParamSweepDialog::pythonScriptName()
{
    // Conventions
    return "multiparam_sweep.py";
}

// Constructors
MultiParamSweepDialog::MultiParamSweepDialog(SweepSpecs runSpecs, QWidget *pParent)
  : BaseRunSpecsDialog(pParent)
{

}
MultiParamSweepDialog::MultiParamSweepDialog(Model model, QWidget *pParent) :
    BaseRunSpecsDialog(pParent)
{
    // Get Model information necessary for the dialog
    QList<QString> variables  = model.getAuxVariables()+model.getOutputVariables();
    QList<QString> parameters = model.getParameters();
    QString modelName         = model.getModelName();
    QString modelFilePath     = model.getFilePath();

    // Default settings
    double startTime  = 0;
    double stopTime   = 1;
    // Initialize the dialog with this info
    initializeDialogWithData(variables, parameters, modelName, modelFilePath, startTime, stopTime);
}
void MultiParamSweepDialog::initializeDialogWithData(QList<QString> variables, QList<QString> parameters, QString modelName, QString modelFilePath, double startTime, double stopTime)
    {
    initializeWindowSettings();

    // Help text description
    QString helpText = readHelpText();
    // Initialize tabs
    QString defaultResultsFolderPath = "/home/omsens/Documents/sweep_results";
    QList<VariableToInclude> vars_to_include =  defaultVariablesToInclude(variables);
    mpSimulationSettingsTab = new SimulationTab(modelName, modelFilePath, startTime, stopTime, defaultResultsFolderPath);
    mpVariablesTab          = new VariablesTab(vars_to_include);
    mpParametersTab         = new ParametersExtendedTab(parameters);
    mpHelpTab               = new HelpTab(helpText);

    // Initialize tabs container widget
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpSimulationSettingsTab, tr("Simulation"));
    mpTabWidget->addTab(mpVariablesTab, tr("Variables"));
    mpTabWidget->addTab(mpParametersTab, tr("Parameters"));
    mpTabWidget->addTab(mpHelpTab, tr("Help"));

    //Buttons
    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("Run Sweep", QDialogButtonBox::AcceptRole);
    mpButtonBox->addButton("Cancel"      , QDialogButtonBox::RejectRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &MultiParamSweepDialog::runMultiParamSweep);
    connect(mpButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mpTabWidget);
    mainLayout->addWidget(mpButtonBox);
    setLayout(mainLayout);
}

QStringList MultiParamSweepDialog::getVarsToAnalyze() const
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

void MultiParamSweepDialog::groupParametersPerturbationsToLists(QList<SweepingParameterPerturbation> &parametersToSweep, QList<FixedParameterPerturbation> &parametersToSetFixedValue) const
{
    QTableWidget *pParamsTable = mpParametersTab->getParametersTable();
    for(int i_row = 0; i_row < pParamsTable->rowCount(); i_row++)
    {
        // Get type of perturbation
        const int pertTypeColPos = mpParametersTab->pertTypeColPos;
        QComboBox *rowComboBox = qobject_cast<QComboBox *>(pParamsTable->cellWidget(i_row,pertTypeColPos));
        QVariant perturbationTypeQVariant = rowComboBox->itemData(rowComboBox->currentIndex());
        int perturbationTypeInt = perturbationTypeQVariant.toInt();

        if(perturbationTypeInt == mpParametersTab->SweepPerturbationId)
        {
            // If the user wants to sweep this param, add it to the sweep list
            // Get param name
            const int paramColPos = mpParametersTab->paramColPos;
            QLabel *paramNameLabel= qobject_cast<QLabel *>(pParamsTable->cellWidget(i_row,paramColPos));
            QString paramNameStr = paramNameLabel->text();
            // Param #iters
            const int paramNItersColPos = mpParametersTab->nItersColPos;
            QSpinBox *paramNItersSpinBox= qobject_cast<QSpinBox *>(pParamsTable->cellWidget(i_row,paramNItersColPos));
            int paramNIters = paramNItersSpinBox->value();
            // Param perturbation percentage
            const int paramPerturbationPercColPos = mpParametersTab->pertRangeColPos;
            QDoubleSpinBox *paramPertPercSpinBox= qobject_cast<QDoubleSpinBox *>(pParamsTable->cellWidget(i_row,paramPerturbationPercColPos));
            double paramPertPerc = paramPertPercSpinBox->value();
            // Create object from info
            SweepingParameterPerturbation sweep_pert = SweepingParameterPerturbation(paramNameStr, paramPertPerc, paramNIters);
            // Add it to the list
            parametersToSweep.append(sweep_pert);
        }
        else if (perturbationTypeInt == mpParametersTab->FixedPerturbationId)
        {
            // Get param name
            const int paramColPos = mpParametersTab->paramColPos;
            QLabel *paramNameLabel= qobject_cast<QLabel *>(pParamsTable->cellWidget(i_row,paramColPos));
            QString paramNameStr = paramNameLabel->text();
            // Get value to set to param
            const int fixedValueColPos = mpParametersTab->fixedValueColPos;
            QDoubleSpinBox *pFixedValueSpinbox = qobject_cast<QDoubleSpinBox *>(pParamsTable->cellWidget(i_row,fixedValueColPos));
            double paramValue = pFixedValueSpinbox->value();
            // Create JSON object from info
            FixedParameterPerturbation fixed_pert = FixedParameterPerturbation(paramNameStr, paramValue);
            // Add it to the list
            parametersToSetFixedValue.append(fixed_pert);
        }
    }
}

QJsonDocument MultiParamSweepDialog::getRunSpecifications() const
{
    // Group parameters from dialog
    QList<SweepingParameterPerturbation> parametersToSweep;
    QList<FixedParameterPerturbation> parametersToSetFixedValue;
    this->groupParametersPerturbationsToLists(parametersToSweep, parametersToSetFixedValue);
    // Initialize specs from dialog info
    SweepSpecs runSpecs = SweepSpecs(
        mpSimulationSettingsTab->getModelPath(),
        mpSimulationSettingsTab->getModelName(),
        mpSimulationSettingsTab->getStartTimeValue(),
        mpSimulationSettingsTab->getStopTimeValue(),
        this->getVarsToAnalyze(),
        parametersToSweep,
        parametersToSetFixedValue
    );
    // It's easier to just return the json doc (concrete class) instead of returning a RunSpecifications (abstract class)
    //   and having to deal with pointers
    QJsonDocument runSpecsDoc = runSpecs.toJson();

    return runSpecsDoc;
}

QString MultiParamSweepDialog::getDestFolderPath() const
{
    // Get folder where to write results
    QString destFolderPath = mpSimulationSettingsTab->getDestFolderPath();
    return destFolderPath;
}

void MultiParamSweepDialog::initializeWindowSettings()
{
    setWindowTitle("Multiparameter Sweep");
    setMinimumWidth(550);
}


void MultiParamSweepDialog::runMultiParamSweep()
{
    // "Return" the run specifications (it has to be read by the caller of the dialog)
    accept();
}

QString MultiParamSweepDialog::readHelpText()
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

QList<VariableToInclude> MultiParamSweepDialog::defaultVariablesToInclude(QList<QString> variables)
{
    QList<VariableToInclude> vars_to_include;
    foreach (QString variable, variables)
    {
        bool default_check = true;
        VariableToInclude var_include = VariableToInclude(variable,default_check);
        vars_to_include.append(var_include);
    }
    return vars_to_include;
}
