#include "MultiParamSweepDialog.h"

#include <QGridLayout>
#include <QHeaderView>
#include <QSizePolicy>
#include <QJsonArray>
#include <QJsonDocument>
#include <QCheckBox>
#include <QTextStream>
#include <QComboBox>

#include "omedit_plugin/model.h"
#include "../../tabs/ParametersExtendedTab.h"
#include "../../tabs/HelpTab.h"
#include "../../tabs/PlotSweepTab.h"

// Constructors
MultiParamSweepDialog::MultiParamSweepDialog(Model model, SweepSpecs runSpecs, QWidget *pParent)
  : BaseRunSpecsDialog(pParent)
{
    // Get specs info
    QList<FixedParameterPerturbation>    fixed_params           = runSpecs.fixed_params;
    QList<SweepingParameterPerturbation> parameters_to_sweep    = runSpecs.parameters_to_sweep;
    double                               start_time             = runSpecs.start_time;
    double                               stop_time              = runSpecs.stop_time;
    QStringList                          exp_vars               = runSpecs.vars_to_analyze;
    bool                                 plot_upper_lower_limit = runSpecs.plot_upper_lower_limit;
    // Get model info
    QList<QString> model_variables  = model.getAuxVariables()+model.getOutputVariables();
    QList<QString> model_parameters = model.getParameters();
    QString        model_name       = model.getModelName();
    QString        model_file_path  = model.getFilePath();


    // Define complex dialog data
    QList<VariableInclusion> vars_inclusion = varsInclusionFromSuperAndSubList(exp_vars, model_variables);
    QList<QString> no_pert_params = model_parameters;
    QList<PerturbationRow> pert_rows = pertRowsFromFIxedAndSweepParamsInfo(fixed_params, parameters_to_sweep, no_pert_params);

    initialize(vars_inclusion, pert_rows, model_name, model_file_path, start_time, stop_time, plot_upper_lower_limit);
}
MultiParamSweepDialog::MultiParamSweepDialog(Model model, QWidget *pParent) :
    BaseRunSpecsDialog(pParent)
{
    // Get Model information necessary for the dialog
    QList<QString> variables  = model.getAuxVariables() + model.getOutputVariables();
    QList<QString> parameters = model.getParameters();
    QString modelName         = model.getModelName();
    QString modelFilePath     = model.getFilePath();

    // Default settings
    double startTime  = 0;
    double stopTime   = 1;
    bool plot_upper_lower_limit = false;
    QList<VariableInclusion> vars_inclusion = defaultVariablesToInclude(variables);
    QList<PerturbationRow> pert_rows        = defaultParametersPerturbations(parameters);

    // Initialize the dialog with this info
    initialize(vars_inclusion, pert_rows, modelName, modelFilePath, startTime, stopTime, plot_upper_lower_limit);
}
void MultiParamSweepDialog::initialize(QList<VariableInclusion> vars_inclusion, QList<PerturbationRow> pert_rows,
                                       QString modelName, QString modelFilePath, double startTime, double stopTime,
                                       bool plot_upper_lower_limit)
{
    initializeWindowSettings();

    // Conventions
    mPythonScriptLibraryPath = "/home/omsens/Documents/OMSens/";
    mPythonScriptPath        = mPythonScriptLibraryPath + "callable_methods/multiparam_sweep.py";
    defaultResultsFolderPath = "/home/omsens/Documents/results_experiments/sweep_results";

    // Help text description
    QString helpText = readHelpText();
    // Initialize tabs
    mpSimulationSettingsTab = new SimulationTab(modelName, modelFilePath, startTime, stopTime, defaultResultsFolderPath);
    mpVariablesTab          = new VariablesTab(vars_inclusion);
    mpParametersTab         = new ParametersExtendedTab(pert_rows);
    mpPlotSweepTab          = new PlotSweepTab(plot_upper_lower_limit);
    mpHelpTab               = new HelpTab(helpText);

    // Initialize tabs container widget
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpSimulationSettingsTab, tr("Simulation"));
    mpTabWidget->addTab(mpVariablesTab, tr("Variables"));
    mpTabWidget->addTab(mpParametersTab, tr("Parameters"));
    mpTabWidget->addTab(mpPlotSweepTab, tr("Plot"));
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
            const int paramColPos = mpParametersTab->nameColPos;
            QTableWidgetItem *nameWidgetItem= pParamsTable->item(i_row,paramColPos);
            QString paramNameStr = nameWidgetItem->text();
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
            const int paramColPos = mpParametersTab->nameColPos;
            QTableWidgetItem *nameWidgetItem= pParamsTable->item(i_row,paramColPos);
            QString paramNameStr = nameWidgetItem->text();
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
        parametersToSetFixedValue,
        mpPlotSweepTab->getUpperLowerLimitCheckbox()
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

QList<VariableInclusion> MultiParamSweepDialog::defaultVariablesToInclude(QList<QString> variables)
{
    QList<VariableInclusion> vars_inclusion;
    foreach (QString variable, variables)
    {
        bool default_check = true;
        VariableInclusion var_include = VariableInclusion(variable,default_check);
        vars_inclusion.append(var_include);
    }
    return vars_inclusion;
}

QList<PerturbationRow> MultiParamSweepDialog::defaultParametersPerturbations(QList<QString> parameters)
{
    QList<PerturbationRow> pert_rows;
    foreach (QString param_name, parameters)
    {
        PerturbationRow row;
        row.name                 = param_name;
        row.perturbation_type_id = default_perturbation_type_id;
        row.iterations           = default_iterations;
        row.percentage           = default_percentage;
        row.fixed_value          = default_fixed_value;
        pert_rows.append(row);
    }

    return pert_rows;
}

QList<VariableInclusion> MultiParamSweepDialog::varsInclusionFromSuperAndSubList(QStringList exp_vars, QList<QString> model_variables)
{
    QList<VariableInclusion> vars_inclusion;
    foreach (QString variable, model_variables)
    {
        bool check = exp_vars.contains(variable);
        VariableInclusion var_include = VariableInclusion(variable,check);
        vars_inclusion.append(var_include);
    }

    return vars_inclusion;
}

QList<PerturbationRow> MultiParamSweepDialog::pertRowsFromFIxedAndSweepParamsInfo(QList<FixedParameterPerturbation> fixed_params, QList<SweepingParameterPerturbation> parameters_to_sweep, QList<QString> no_pert_params)
{
    QList<PerturbationRow> pert_rows;
    // Iterate fixed params
    foreach (FixedParameterPerturbation param_pert, fixed_params)
    {
        // Set the values for this type of perturbation and the rest to default
        PerturbationRow row;
        row.name                 = param_pert.name;
        row.perturbation_type_id = ParametersExtendedTab::FixedPerturbationId;
        row.iterations           = default_iterations;
        row.percentage           = default_percentage;
        row.fixed_value          = param_pert.value;
        pert_rows.append(row);
        // Pop this param from the no pert params list
        no_pert_params.removeOne(param_pert.name);
    }
    // Iterate sweep params
    foreach (SweepingParameterPerturbation param_pert, parameters_to_sweep)
    {
        // Set the values for this type of perturbation and the rest to default
        PerturbationRow row;
        row.name                 = param_pert.name;
        row.perturbation_type_id = ParametersExtendedTab::SweepPerturbationId;
        row.iterations           = param_pert.iterations;
        row.percentage           = param_pert.delta_percentage;
        row.fixed_value          = default_fixed_value;
        pert_rows.append(row);
        // Pop this param from the no pert params list
        no_pert_params.removeOne(param_pert.name);
    }
    // Iterate no pert params
    foreach (QString param_name, no_pert_params)
    {
        // Set the values for this type of perturbation and the rest to default
        PerturbationRow row;
        row.name                 = param_name;
        row.perturbation_type_id = ParametersExtendedTab::NoPerturbationId;
        row.iterations           = default_iterations;
        row.percentage           = default_percentage;
        row.fixed_value          = default_fixed_value;
        pert_rows.append(row);
    }

    return pert_rows;
}
