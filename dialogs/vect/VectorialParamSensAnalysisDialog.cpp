#include "VectorialParamSensAnalysisDialog.h"

#include <QMessageBox>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>
#include <QJsonArray>
#include <QTextStream>

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
    mpSimulationSettingsTab = new SimulationTab(modelName, modelFilePath, startTime, stopTime, defaultResultsFolderPath);
    mpParametersTab         = new ParametersSimpleTab(parameters, percentage);
    mpOptimizationTab       = new OptimizationTab(variables);
    mpHelpTab               = new HelpTab(helpText);

    // Initialize tabs container widget
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpSimulationSettingsTab, tr("Simulation"));
    mpTabWidget->addTab(mpParametersTab, tr("Parameters"));
    mpTabWidget->addTab(mpOptimizationTab, tr("Optimization"));
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
