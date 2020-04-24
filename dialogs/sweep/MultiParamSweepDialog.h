#ifndef MULTIPARAMSWEEPDIALOG_H
#define MULTIPARAMSWEEPDIALOG_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QFrame>
#include <QGridLayout>
#include <QTableWidget>
#include <QDialogButtonBox>
#include <QJsonObject>
#include <QString>
#include "../../tabs/SimulationTab.h"
#include "../../tabs/VariablesTab.h"
#include "../../tabs/ParametersExtendedTab.h"
#include "../../tabs/HelpTab.h"
#include "../../tabs/PlotSweepTab.h"
#include "../../DualLists.h"
#include "omedit_plugin/model.h"
#include "../BaseRunSpecsDialog.h"
#include "../../specs/SweepSpecs.h"


class MultiParamSweepDialog : public BaseRunSpecsDialog
{
    Q_OBJECT
public:
    // Constructors
    MultiParamSweepDialog(Model model, SweepSpecs runSpecs, QWidget *pParent = 0);
    MultiParamSweepDialog(Model model, QWidget *pParent = 0);

    // Getters
    QJsonDocument getRunSpecifications() const;
    QString getDestFolderPath() const;

    QString helpTextPath = ":/OMSens/sweep/help.html";
    // Conventions for parameters perturbation rows
    int    default_perturbation_type_id = ParametersExtendedTab::NoPerturbationId;
    int    default_iterations           = 3;
    double default_percentage           = 5;
    double default_fixed_value          = 0;

private:
    void initialize(QList<VariableInclusion> vars_inclusion, QList<PerturbationRow> pert_rows, QString modelName,
                    QString modelFilePath, double startTime, double stopTime, bool plot_upper_lower_limit);
    // GUI members
    QTabWidget            *mpTabWidget;
    SimulationTab         *mpSimulationSettingsTab;
    PlotSweepTab          *mpPlotSweepTab;
    VariablesTab          *mpVariablesTab;
    ParametersExtendedTab *mpParametersTab;
    HelpTab               *mpHelpTab;
    QDialogButtonBox      *mpButtonBox;

    // Auxs:
    void initializeWindowSettings();
    QString readHelpText();
    QStringList getVarsToAnalyze() const;
    void groupParametersPerturbationsToLists(QList<SweepingParameterPerturbation> &parametersToSweep, QList<FixedParameterPerturbation> &parametersToSetFixedValue) const;
    QList<VariableInclusion> defaultVariablesToInclude(QList<QString> variables);
    QList<PerturbationRow> defaultParametersPerturbations(QList<QString> parameters);
    QList<VariableInclusion> varsInclusionFromSuperAndSubList(QStringList exp_vars, QList<QString> model_variables);
    QList<PerturbationRow> pertRowsFromFIxedAndSweepParamsInfo(QList<FixedParameterPerturbation> fixed_params, QList<SweepingParameterPerturbation> parameters_to_sweep, QList<QString> no_pert_params);

private slots:
    void runMultiParamSweep();
};

#endif // MULTIPARAMSWEEPDIALOG_H
