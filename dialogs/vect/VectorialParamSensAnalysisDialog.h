#ifndef VECTORIALPARAMSENSANALYSISDIALOG_H
#define VECTORIALPARAMSENSANALYSISDIALOG_H

#include <QDialog>
#include <QFrame>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QJsonObject>
#include "omedit_plugin/model.h"
#include "../../tabs/SimulationTab.h"
#include "../../tabs/ParametersSimpleTab.h"
#include "../../tabs/OptimizationTab.h"
#include "../../tabs/HelpTab.h"
#include "../BaseRunSpecsDialog.h"
#include "../../specs/VectSpecs.h"
#include "../../tabs/PlotOptimizationTab.h"

class VectorialSensAnalysisDialog : public BaseRunSpecsDialog
{
    Q_OBJECT
public:
    // Constructors
    VectorialSensAnalysisDialog(Model model, VectSpecs runSpecs, QWidget *pParent = 0);
    VectorialSensAnalysisDialog(Model model, QWidget *pParent = 0);
    // Getters
    QJsonDocument getRunSpecifications() const;
    QString getDestFolderPath() const;

private:
    void initialize(QList<QString> variables, QString target_var, bool maximize,
                    double epsilon, QList<ParameterInclusion> params_inclusion,
                    QString modelName, QString modelFilePath,
                    double percentage, double startTime, double stopTime,
                    QString optimizer_name, QString objective_function_name, double alpha_value,
                    QString constrained_time_path_file, QString constrained_variable, double constrained_epsilon,
                    bool plot_restriction, bool plot_std_run
                    );
    // GUI members
    QTabWidget            *mpTabWidget;
    SimulationTab         *mpSimulationSettingsTab;
    ParametersSimpleTab   *mpParametersTab;
    OptimizationTab       *mpOptimizationTab;
    PlotOptimizationTab   *mpPlotOptimizationTab;
    HelpTab               *mpHelpTab;
    QDialogButtonBox      *mpButtonBox;

    // Conventions
    QString helpTextPath = ":/OMSens/vect/help.html";

    // Aux functions
    void initializeWindowSettings();
    QString readHelpText();
    QList<ParameterInclusion> defaultParametersToInclude(QList<QString> parameters);
    QList<ParameterInclusion> paramsInclusionFromSuperAndSubList(QStringList exp_params, QList<QString> model_parameters);
    QStringList getParametersToPerturb() const;
    bool getIfMaximization() const;

private slots:
    void runVectorialParamSensAnalysis();
};

#endif // VECTORIALPARAMSENSANALYSISDIALOG_H
