#include "VectorialParamSensAnalysisDialog.h"

#include <QMessageBox>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>

// Constructors
VectorialSensAnalysisDialog::VectorialSensAnalysisDialog(Model model, VectSpecs runSpecs, QWidget *pParent)
  : BaseRunSpecsDialog(pParent)
{
    // Get specs info
    double percentage        = runSpecs.percentage;
    double startTime         = runSpecs.start_time;
    double stopTime          = runSpecs.stop_time;
    double epsilon           = runSpecs.epsilon;
    QString exp_target_var   = runSpecs.target_var;
    QStringList exp_params   = runSpecs.parameters_to_perturb;
    bool exp_maximize        = runSpecs.maximize;

    QString optimizer_name = runSpecs.optimizer_name;
    QString objective_function_name = runSpecs.objective_function_name;
    double alpha_value = runSpecs.alpha_value;
    QString constrained_time_path_file = runSpecs.constrained_time_path_file;
    QString constrained_variable = runSpecs.constrained_variable;
    double constrained_epsilon = runSpecs.constrained_epsilon;

    bool plot_restriction = runSpecs.plot_restriction;
    bool plot_std_run     = runSpecs.plot_std_run;

    // Get model info
    QList<QString> model_variables  = model.getAuxVariables() + model.getOutputVariables();
    QList<QString> model_parameters = model.getParameters();
    QString model_name              = model.getModelName();
    QString model_file_path         = model.getFilePath();

    // Define complex dialog data
    QList<ParameterInclusion> params_inclusion = paramsInclusionFromSuperAndSubList(exp_params, model_parameters);

    // Call the initializer with the parsed data from the specs
    initialize(model_variables, exp_target_var, exp_maximize,
               epsilon, params_inclusion, model_name,
               model_file_path, percentage, startTime, stopTime,
               optimizer_name, objective_function_name, alpha_value,
               constrained_time_path_file, constrained_variable, constrained_epsilon,
               plot_restriction, plot_std_run
    );
}
VectorialSensAnalysisDialog::VectorialSensAnalysisDialog(Model model, QWidget *pParent) :
  BaseRunSpecsDialog(pParent)
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

    double epsilon    = 0.1;
    double constrained_epsilon_initial = 0.1;
    QString optimizer_name = "CURVIFGR";
    QString objective_function_name = "Alpha weighted path constrained";
    double alpha_value = 0.5;
    QString constrained_time_path_file = "/home/omsens/limit_path.csv";

    bool plot_restriction = false;
    bool plot_std_run = false;

    QList<ParameterInclusion> params_inclusion = defaultParametersToInclude(parameters);
    QString target_var = variables.first();
    bool   maximize = true;

    initialize(variables, target_var, maximize, epsilon,
               params_inclusion, modelName, modelFilePath,
               percentage, startTime, stopTime,
               optimizer_name, objective_function_name,
               alpha_value, constrained_time_path_file, target_var, constrained_epsilon_initial,
               plot_restriction, plot_std_run);
}

void VectorialSensAnalysisDialog::initializeWindowSettings()
{
    setWindowTitle("Vectorial Parameter Based Sensitivity Analysis");
    setMinimumWidth(550);
}

void VectorialSensAnalysisDialog::initialize(QList<QString> variables, QString target_var,
                                             bool maximize, double epsilon, QList<ParameterInclusion> params_inclusion,
                                             QString modelName, QString modelFilePath, double percentage,
                                             double startTime, double stopTime,
                                             QString optimizer_name, QString objective_function_name, double alpha_value,
                                             QString constrained_time_path_file, QString constrained_variable, double constrained_epsilon,
                                             bool plot_restriction, bool plot_std_run
                                             )
    {
    initializeWindowSettings();

    // Conventions
    mPythonScriptLibraryPath = "/home/omsens/Documents/OMSens/";
    mPythonScriptPath        = mPythonScriptLibraryPath + "callable_methods/vectorial_analysis.py";
    defaultResultsFolderPath = "/home/omsens/Documents/results_experiments/vectorial_analysis";

    // Help text description
    QString helpText = readHelpText();

    mpSimulationSettingsTab = new SimulationTab(modelName, modelFilePath, startTime, stopTime, defaultResultsFolderPath);
    QString parametersQuickExplanation = "The parameters will be perturbed together to find the best combination of values.";
    mpParametersTab         = new ParametersSimpleTab(params_inclusion, parametersQuickExplanation);
    mpOptimizationTab       = new OptimizationTab(
                variables, target_var, epsilon, percentage, maximize,
                optimizer_name, objective_function_name, alpha_value, constrained_time_path_file,
                constrained_variable, constrained_epsilon
                );
    mpPlotOptimizationTab   = new PlotOptimizationTab(plot_restriction, plot_std_run);
    mpHelpTab               = new HelpTab(helpText);

    // Initialize tabs container widget
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpSimulationSettingsTab, tr("Simulation"));
    mpTabWidget->addTab(mpParametersTab, tr("Parameters"));
    mpTabWidget->addTab(mpOptimizationTab, tr("Optimization"));
    mpTabWidget->addTab(mpPlotOptimizationTab, tr("Plots"));
    mpTabWidget->addTab(mpHelpTab, tr("Help"));

    //Buttons
    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("Run analysis", QDialogButtonBox::AcceptRole);
    mpButtonBox->addButton("Cancel"      , QDialogButtonBox::RejectRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &VectorialSensAnalysisDialog::runVectorialParamSensAnalysis);
    connect(mpButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mpTabWidget);
    mainLayout->addWidget(mpButtonBox);
    setLayout(mainLayout);
}

QStringList VectorialSensAnalysisDialog::getParametersToPerturb() const
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

bool VectorialSensAnalysisDialog::getIfMaximization() const
{
    int goalButtonId = mpOptimizationTab->getGoalId();
    bool maximize;
    if(goalButtonId == mpOptimizationTab->mMinimizeButtonId)
        maximize = false;
    else if(goalButtonId == mpOptimizationTab->mMaximizeButtonId)
        maximize = true;
    return maximize;
}

QJsonDocument VectorialSensAnalysisDialog::getRunSpecifications() const
{
    // Initialize specs from dialog info
    VectSpecs runSpecs = VectSpecs(
        mpSimulationSettingsTab->getModelPath(),
        mpSimulationSettingsTab->getModelName(),
        getIfMaximization(),
        getParametersToPerturb(),
        mpOptimizationTab->getEpsilon(),
        mpOptimizationTab->getBoundariesValue(),
        mpSimulationSettingsTab->getStartTimeValue(),
        mpSimulationSettingsTab->getStopTimeValue(),
        mpSimulationSettingsTab->getRestrictionPath(),

        mpOptimizationTab->getTargetVariable(),
        mpOptimizationTab->getOptimizerName(),
        mpOptimizationTab->getObjectiveFunctionName(),
        mpOptimizationTab->getAlphaValue(),
        mpOptimizationTab->getConstrainedTimePathFile(),
        mpOptimizationTab->getConstrainedVariable(),
        mpOptimizationTab->getConstrainedEpsilon(),

        mpPlotOptimizationTab->getRestrictionCheckbox(),
        mpPlotOptimizationTab->getStandardRunCheckbox()
    );

    // It's easier to just return the json doc (concrete class) instead of returning a RunSpecifications (abstract class)
    //   and having to deal with pointers
    QJsonDocument runSpecsDoc = runSpecs.toJson();
    return runSpecsDoc;
}

QString VectorialSensAnalysisDialog::getDestFolderPath() const
{
    QString destFolderPath = mpSimulationSettingsTab->getDestFolderPath();
    return destFolderPath;
}

void VectorialSensAnalysisDialog::runVectorialParamSensAnalysis()
{
    // Just accept for now
    accept();
}

QString VectorialSensAnalysisDialog::readHelpText()
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

QList<ParameterInclusion> VectorialSensAnalysisDialog::defaultParametersToInclude(QList<QString> parameters)
{
    QList<ParameterInclusion> params_inclusion;
    foreach (QString param, parameters)
    {
        bool default_check = false;
        ParameterInclusion param_include = ParameterInclusion(param,default_check);
        params_inclusion.append(param_include);
    }
    return params_inclusion;
}

QList<ParameterInclusion> VectorialSensAnalysisDialog::paramsInclusionFromSuperAndSubList(QStringList exp_params, QList<QString> model_parameters)
{
    QList<ParameterInclusion> params_inclusion;
    foreach (QString param, model_parameters)
    {
        bool check = exp_params.contains(param);
        ParameterInclusion param_include = ParameterInclusion(param,check);
        params_inclusion.append(param_include);
    }

    return params_inclusion;
}
