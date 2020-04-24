#ifndef INDIVPARAMSENSANALYSISDIALOG_H
#define INDIVPARAMSENSANALYSISDIALOG_H
#include "omedit_plugin/model.h"
#include "../../tabs/VariablesTab.h"
#include "../../tabs/ParametersSimpleTab.h"
#include "../../tabs/SimulationTab.h"
#include "../../tabs/HelpTab.h"
#include "../../tabs/PerturbationTab.h"
#include "../BaseRunSpecsDialog.h"
#include "../../specs/IndivSpecs.h"

#include <QDialog>
#include <QFrame>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QJsonObject>
#include <QDialogButtonBox>

class IndivParamSensAnalysisDialog : public BaseRunSpecsDialog
{
    Q_OBJECT
public:
    // Constructors
    IndivParamSensAnalysisDialog(Model model, IndivSpecs runSpecs, QWidget *pParent = 0);
    IndivParamSensAnalysisDialog(Model model, QWidget *pParent = 0);
    // Getters
    QJsonDocument getRunSpecifications() const;
    QString getDestFolderPath() const;
    QStringList getVarsToAnalize() const;
    QStringList getParametersToPerturb() const;

private:
    // GUI members
    QTabWidget          *mpTabWidget;
    SimulationTab       *mpSimulationSettingsTab;
    VariablesTab        *mpVariablesTab;
    ParametersSimpleTab *mpParametersTab;
    HelpTab             *mpHelpTab;
    PerturbationTab     *mpPerturbationTab;
    QDialogButtonBox    *mpButtonBox;

    // Conventions
    QString helpTextPath = ":/OMSens/indiv/help.html";

    // Auxs
    void initialize(QList<VariableInclusion> vars_to_include, QList<ParameterInclusion> parameters, QString modelName, QString modelFilePath, double percentage, double startTime, double stopTime);
    void initializeWindowSettings();
    void setHeading();
    void initializeFormInputsAndLabels(const double min_perturbation_perc, const double max_perturbation_perc, const double max_target_time, const QVector<QString> methods);
    void initializeButton();
    void addWidgetsToLayout(QGridLayout *pMainLayout);
    QGridLayout * initializeLayout();
    QList<QString> fromListOfVariantToListOfStr(QList<QVariant> listOfQVariant);
    QString readHelpText();
    QList<VariableInclusion> defaultVariablesToInclude(QList<QString> variables);
    QList<ParameterInclusion> defaultParametersToInclude(QList<QString> parameters);
    QList<VariableInclusion> varsInclusionFromSuperAndSubList(QStringList exp_vars, QList<QString> model_variables);
    QList<ParameterInclusion> paramsInclusionFromSuperAndSubList(QStringList exp_params, QList<QString> model_parameters);


private slots:
  void runIndivParamSensAnalysis();
};

#endif // INDIVPARAMSENSANALYSISDIALOG_H
