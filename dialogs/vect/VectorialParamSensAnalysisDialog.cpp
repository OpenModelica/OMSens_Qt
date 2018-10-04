#include "VectorialParamSensAnalysisDialog.h"

#include "Util/Utilities.h"
#include <QMessageBox>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>
#include <QJsonArray>

VectorialSensAnalysisDialog::VectorialSensAnalysisDialog(Model model, QWidget *pParent) :
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

    initializeDialogWithData(variables, parameters, modelName, modelFilePath, percentage, startTime, stopTime);
//    // Function parameters
//    const double defaultTime= 2000;
//    const double maxTargetTime= 5000;
//    const double maxPerturbationPercentage= 100;
//    const double minPerturbationPercentage= -100;
//    initializeFormInputsAndLabels(maxTargetTime, maxPerturbationPercentage, defaultTime, minPerturbationPercentage);
//    initializeButton();
//    QGridLayout *pMainLayout = initializeLayout();
//    addWidgetsToLayout(pMainLayout);
//    // QWidget function to set layout to "this"
//    setLayout(pMainLayout);
}

void VectorialSensAnalysisDialog::initializeWindowSettings()
{
    setWindowTitle("Vectorial Parameter Based Sensitivity Analysis");
    setMinimumWidth(550);
}

void VectorialSensAnalysisDialog::initializeDialogWithData(QList<QString> variables, QList<QString> parameters, QString modelName, QString modelFilePath, double percentage, double startTime, double stopTime)
    {
    initializeWindowSettings();

    // Help text description
    QString helpText = "<p>This routine uses an optimization algorithm to find the values of a set of"
            "parameters that maximize/minimize a chosen variable. It's able to do this by"
            "characterizing the dynamic models as nonlinear programming problems.</p>"
            "<p>It can be used to analyze how a set of parameters behave when perturbed "
            "together, instead of analyzing isolated perturbations. This further increases"
            "the chances of finding, for example, a combination of small parameter"
            "perturbations that has a non-negligible effect on a variable, possibly showing"
            "that the model is not as robust as previously thought.</p>"
            "<p>Nevertheless, this analysis may take several minutes, maybe hours, depending "
            "on<br />the following:</p>"
            "<ul> "
            "<li>The complexity of the model. Simpler models take less time to "
            "simulate.</li>"
            "<li>The number of parameters to analyze. Each parameter has to be combined with "
            "all the others. This means that no matter how effective the underlying "
            "optimization algorithm is, in the worst case scenario the analysis time"
            "is affected exponentially by the number of parameters to analyze.</li>"
            "<li>The simulation time. The shorter the internal simulation time then the "
            "shorter the execution time of the simulations.</li>"
            "<li>The epsilon. A smaller epsilon may find a better solution but at the "
            "expense of longer analysis time.</li>"
            "<li>The bounds percentage. The larger the bounds of the parameters, the more"
            "values the optimization algorithm has to test.</li>"
            "<li>The system: number of processors, disk speeds, etc.</li>"
            "</ul>"
            "<p><strong>Known limitations</strong></p>"
            "<p>Only parameters and variables of type Real are recognized. Not even renamings of the sort of 'type MyType = Real' are supported.</p>"
            "<p>Arrays of any type are not supported either.</p>";
    // Initialize tabs
    QString defaultResultsFolderPath = "/home/omsens/Documents/vectorial_analysis";
    mpSimulationSettingsTab = new SimulationTab(modelName, modelFilePath, startTime, stopTime, defaultResultsFolderPath,this);
    mpParametersTab         = new ParametersSimpleTab(parameters, percentage,this);
    mpOptimizationTab       = new OptimizationTab(variables,this);
    mpHelpTab               = new HelpTab(helpText,this);

    // Initialize tabs container widget
    mpTabWidget = new QTabWidget(this);
    mpTabWidget->addTab(mpSimulationSettingsTab, tr("Simulation"));
    mpTabWidget->addTab(mpParametersTab, tr("Parameters"));
    mpTabWidget->addTab(mpOptimizationTab, tr("Optimization"));
    mpTabWidget->addTab(mpHelpTab, tr("Help"));

    //Buttons
    mpButtonBox = new QDialogButtonBox(this);
    mpButtonBox->addButton("Run analysis", QDialogButtonBox::AcceptRole);
    mpButtonBox->addButton("Cancel"      , QDialogButtonBox::RejectRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &VectorialSensAnalysisDialog::runVectorialParamSensAnalysis);
    connect(mpButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(mpTabWidget);
    mainLayout->addWidget(mpButtonBox);
    setLayout(mainLayout);
}

// void VectorialSensAnalysisDialog::initializeUpperAndLowerBoundsForms(const double minPerturbationPercentage, const double maxPerturbationPercentage)
// {
//     mpLowerBoundLabel = new Label(tr("Lower Bound:"), this);
//     mpLowerBoundBox = new QDoubleSpinBox(this);
//     mpLowerBoundBox->setRange(minPerturbationPercentage, 0);
//     mpLowerBoundBox->setValue(-5);
//     mpLowerBoundBox->setSuffix("%");
//     mpUpperBoundLabel = new Label(tr("Upper Bound:"), this);
//     mpUpperBoundBox = new QDoubleSpinBox(this);
//     mpUpperBoundBox->setRange(0, maxPerturbationPercentage);
//     mpUpperBoundBox->setValue(5);
//     mpUpperBoundBox->setSuffix("%");
// }
//
// void VectorialSensAnalysisDialog::initializeVarForms()
// {
//     mpVariableLabel = new Label(tr("Target Variable:"), this);
//     // The button group is purely backend specific. No effect on the GUI
//     mpOptimTypeButtonGroup = new QButtonGroup(this);
//     mpMaxRadio = new QRadioButton(tr("Maximize"),this);
//     mpMaxRadio->toggle(); //This index start selected by default
//     mpMinRadio = new QRadioButton(tr("Minimize"),this);
//     mpOptimTypeButtonGroup->addButton(mpMinRadio, 0);
//     mpOptimTypeButtonGroup->addButton(mpMaxRadio, 1);
//
//     mpVariableComboBox = new QComboBox(this);
//     QList<QString> outputVariables = model.getOutputVariables();
//     for (int i_vars=0; i_vars<outputVariables.size(); i_vars++)
//     {
//         mpVariableComboBox->addItem(outputVariables[i_vars], QVariant(i_vars));
//     }
// }
//
// void VectorialSensAnalysisDialog::initializeParameterForms()
// {
//     mpParameterLabel = new Label(tr("Parameters to perturb:"),this);
//     // Dual Lists. On the left are the options to select and on the right the selected options
//     mpParametersDualLists = new DualLists(this);
//     QList<QString> parameters = model.getParameters();
//     for (int i_params=0; i_params<parameters.size(); i_params++)
//     {
//         mpParametersDualLists->addItemToLeftList(parameters[i_params]);
//     }
//
// }
//
// void VectorialSensAnalysisDialog::initializeTimeForms(const double defaultTime, const double maxTargetTime)
// {
//     mpTimeLabel = new Label(tr("Time:"),this);
//     mpTimeBox = new QDoubleSpinBox(this);
//     mpTimeBox->setRange(0, maxTargetTime);
//     mpTimeBox->setValue(defaultTime);
// }
//
// void VectorialSensAnalysisDialog::initializeFormInputsAndLabels(const double maxTargetTime, const double maxPerturbationPercentage, const double defaultTime, const double minPerturbationPercentage)
// {
//     initializeUpperAndLowerBoundsForms(minPerturbationPercentage, maxPerturbationPercentage);
//     initializeVarForms();
//     initializeParameterForms();
//     initializeTimeForms(defaultTime, maxTargetTime);
// }
//
// void VectorialSensAnalysisDialog::initializeButton()
// {
//     // create OK button
//     mpRunButton = new QPushButton("Ok", this);
//     mpRunButton->setAutoDefault(true);
//     connect(mpRunButton, SIGNAL(clicked()), SLOT(runVectorialParamSensAnalysis()));
// }
//
// QGridLayout * VectorialSensAnalysisDialog::initializeLayout()
// {
//     // set grid layout
//     QGridLayout *pMainLayout = new QGridLayout(this);
//     pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
//
//     return pMainLayout;
// }
//
// void VectorialSensAnalysisDialog::addWidgetsToLayout(QGridLayout *pMainLayout)
// {
//     pMainLayout->addWidget(mpHeading, 0, 0, 1, 3);
//     pMainLayout->addWidget(mpHorizontalLine, 1, 0, 1, 3);
//     pMainLayout->addWidget(mpLowerBoundLabel, 2, 0);
//     pMainLayout->addWidget(mpLowerBoundBox, 2, 1);
//     pMainLayout->addWidget(mpUpperBoundLabel, 2, 2);
//     pMainLayout->addWidget(mpUpperBoundBox, 2, 3);
//     pMainLayout->addWidget(mpVariableLabel, 5, 0);
//     pMainLayout->addWidget(mpMaxRadio, 5, 1);
//     pMainLayout->addWidget(mpMinRadio, 6, 1);
//     pMainLayout->addWidget(mpVariableComboBox, 5, 2);
//     pMainLayout->addWidget(mpParameterLabel, 7, 0);
//     pMainLayout->addWidget(mpParametersDualLists,7, 1, 1, 3);
//     pMainLayout->addWidget(mpTimeLabel, 8, 0);
//     pMainLayout->addWidget(mpTimeBox, 8, 1);
//
//     pMainLayout->addWidget(mpRunButton, 10, 0, 1, 3, Qt::AlignRight);
// }

QJsonObject VectorialSensAnalysisDialog::getRunSpecifications() const
{
    return mRunSpecifications;
}

QString VectorialSensAnalysisDialog::getDestFolderPath() const
{
    return mpDestFolderPath;
}

void VectorialSensAnalysisDialog::runVectorialParamSensAnalysis()
{
    // Get folder where to write results
    //mpDestFolderPath = new QString(mpSimulationSettingsTab->getDestFolderPath());
    mpDestFolderPath = mpSimulationSettingsTab->getDestFolderPath();
    // Instantiate a JSON Qt object with analysis specs
    mRunSpecifications["model_name"]      = mpSimulationSettingsTab->getModelName();
    mRunSpecifications["model_mo_path"]   = mpSimulationSettingsTab->getModelPath();
    mRunSpecifications["start_time"]      = mpSimulationSettingsTab->getStartTimeValue();
    mRunSpecifications["stop_time"]       = mpSimulationSettingsTab->getStopTimeValue();
    mRunSpecifications["percentage"]      = mpParametersTab->getPercentageValue();
    mRunSpecifications["epsilon"]         = mpOptimizationTab->getEpsilon();
    mRunSpecifications["target_var_name"] = mpOptimizationTab->getTargetVariable();
    // Goal
    int goalButtonId = mpOptimizationTab->getGoalId();
    QString goalString;
    if(goalButtonId == mpOptimizationTab->mMinimizeButtonId)
        goalString = "min";
    else
        goalString = "max";
    mRunSpecifications["max_or_min"]      = goalString;
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
    // "Return" the run specifications (it has to be read by the caller of the dialog)
    accept();
}
