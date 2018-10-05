#include "MultiParamSweepDialog.h"

#include <QGridLayout>
#include <QHeaderView>
#include <QSizePolicy>
#include <QJsonArray>
#include <QCheckBox>

#include "../../model.h"
#include "../../tabs/ParametersExtendedTab.h"
#include "../../tabs/HelpTab.h"

MultiParamSweepDialog::MultiParamSweepDialog(Model model, QWidget *pParent) :
    QDialog(pParent)
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
void MultiParamSweepDialog::initializeDialogWithData(QList<QString> variables, QList<QString> parameters, QString modelName, QString modelFilePath, double percentage, double startTime, double stopTime)
    {
    initializeWindowSettings();

    // Help text description
    QString helpText = "<p><strong>Multiparameter sweep</strong></p>"
            "<p>Launches several simulations covering all the possible combinations of parameters values as indicated by the user. If, for example, our model has 2 parameters with the following <br>"
            "default values, p1= 10 and p2 = 100; and we want to perturb them as:</p>"
            "<ul>"
            "<li>p1: 2 iterations of &plusmn;5% perturbation"
            "<ul>"
            "<li>10*(1-5/100) = 9.5</li>"
            "<li>10*(1+5/100) = 10.5</li>"
            "</ul>"
            "</li>"
            "<li>p2: 3 iterations of &plusmn;10% perturbation"
            "<ul>"
            "<li>100*(1-10/100) = 95</li>"
            "<li>100</li>"
            "<li>100 *(1+10/100) = 110</li>"
            "</ul>"
            "</li>"
            "</ul>"
            "<p>Then, this will result in 6 iterations (2 possible values for p1 and 3 for p2). The corresponding simulations will be:</p>"
            "<ul>"
            "<li>Simulation 1: p1 = 9.5, p2 = 90</li>"
            "<li>Simulation 2: p1 = 9.5, p2 = 100</li>"
            "<li>Simulation 3: p1 = 9.5, p2 = 110</li>"
            "<li>Simulation 4: p1 = 10.5, p2 = 90</li>"
            "<li>Simulation 5: p1 = 10.5, p2 = 100</li>"
            "<li>Simulation 6: p1 = 10.5, p2 = 110</li>"
            "<li>Simulation 7: p1 = 10, p2 = 100 (a standard run is always included)</li>"
            "</ul>"
            "<p><strong>Known limitations</strong></p>"
            "<p>Only parameters and variables of type Real are recognized. Not even renamings of the sort of 'type MyType = Real' are supported.</p>"
            "<p>Arrays of any type are not supported either.</p>";
    // Initialize tabs
    QString defaultResultsFolderPath = "/home/omsens/Documents/sweep_results";
    mpSimulationSettingsTab = new SimulationTab(modelName, modelFilePath, startTime, stopTime, defaultResultsFolderPath);
    mpVariablesTab          = new VariablesTab(variables);
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

QJsonObject MultiParamSweepDialog::getRunSpecifications() const
{
    return mRunSpecifications;
}

QString MultiParamSweepDialog::getDestFolderPath() const
{
    return mpDestFolderPath;
}

void MultiParamSweepDialog::initializeWindowSettings()
{
    setWindowTitle("Multiparameter Sweep");
    setMinimumWidth(550);
}


void MultiParamSweepDialog::runMultiParamSweep()
{
    // Get folder where to write results
    mpDestFolderPath = mpSimulationSettingsTab->getDestFolderPath();
    // Instantiate a JSON Qt object with analysis specs
    mRunSpecifications["model_name"]    = mpSimulationSettingsTab->getModelName();
    mRunSpecifications["model_mo_path"] = mpSimulationSettingsTab->getModelPath();
    mRunSpecifications["start_time"]    = mpSimulationSettingsTab->getStartTimeValue();
    mRunSpecifications["stop_time"]     = mpSimulationSettingsTab->getStopTimeValue();
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
            // Param #iters
            const int paramNItersColPos = mpParametersTab->nItersColPos;
            QSpinBox *paramNItersSpinBox= qobject_cast<QSpinBox *>(pParamsTable->cellWidget(i_row,paramNItersColPos));
            int paramNIters = paramNItersSpinBox->value();
            // Param perturbation percentage
            const int paramPerturbationPercColPos = mpParametersTab->pertPercColPos;
            QDoubleSpinBox *paramPertPercSpinBox= qobject_cast<QDoubleSpinBox *>(pParamsTable->cellWidget(i_row,paramPerturbationPercColPos));
            double paramPertPerc = paramPertPercSpinBox->value();
            // Create JSON object from info
            QJsonObject param_info;
            param_info["name"]              = paramNameStr;
            param_info["iterations"]        = paramNIters;
            param_info["delta_percentage"]  = paramPertPerc;
            // Add it to the list
            parametersToPerturb.append(param_info);
        }
    }
    mRunSpecifications["parameters_to_sweep"] = parametersToPerturb;
    // "Return" the run specifications (it has to be read by the caller of the dialog)
    accept();
}
