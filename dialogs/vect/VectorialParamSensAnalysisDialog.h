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
#include "../../model.h"
#include "../../tabs/SimulationTab.h"
#include "../../tabs/ParametersSimpleTab.h"
#include "../../tabs/OptimizationTab.h"
#include "../../tabs/HelpTab.h"

class VectorialSensAnalysisDialog : public QDialog
{
    Q_OBJECT
public:
    VectorialSensAnalysisDialog(Model model, QWidget *pParent = 0);

    // Getters
    QJsonObject getRunSpecifications() const;
    QString getDestFolderPath() const;
private:
    void initializeDialogWithData(QList<QString> variables, QList<QString> parameters, QString modelName, QString modelFilePath, double percentage, double startTime, double stopTime);
    // GUI members
    QTabWidget            *mpTabWidget;
    SimulationTab         *mpSimulationSettingsTab;
    ParametersSimpleTab   *mpParametersTab;
    OptimizationTab       *mpOptimizationTab;
    HelpTab               *mpHelpTab;
    QDialogButtonBox      *mpButtonBox;

    // Dialog "return" members
    QJsonObject mRunSpecifications;
    QString     mpDestFolderPath;

//    // Model information members
//    Model model;
//    // GUI members
//    Label *mpHeading;
//    QFrame *mpHorizontalLine;
//    Label *mpLowerBoundLabel;
//    QDoubleSpinBox *mpLowerBoundBox;
//    Label *mpUpperBoundLabel;
//    QDoubleSpinBox *mpUpperBoundBox;
//    Label *mpVariableLabel;
//    QComboBox *mpVariableComboBox;
//    QButtonGroup *mpOptimTypeButtonGroup;
//    QRadioButton *mpMaxRadio;
//    QRadioButton *mpMinRadio;
//    Label *mpParameterLabel;
//    DualLists *mpParametersDualLists;
//    Label *mpTimeLabel;
//    QDoubleSpinBox *mpTimeBox;
//    QPushButton *mpRunButton;

    // Aux functions
    void initializeWindowSettings();
//    void initializeFormInputsAndLabels(const double maxTargetTime, const double maxPerturbationPercentage, const double defaultTime, const double minPerturbationPercentage);
//    void initializeButton();
//    QGridLayout * initializeLayout();
//    void addWidgetsToLayout(QGridLayout *pMainLayout);
//    void initializeVarForms();
//    void initializeParameterForms();
//    void initializeTimeForms(const double defaultTime, const double maxTargetTime);
//    void initializeUpperAndLowerBoundsForms(const double minPerturbationPercentage, const double maxPerturbationPercentage);
//
signals:

private slots:
    void runVectorialParamSensAnalysis();
};

#endif // VECTORIALPARAMSENSANALYSISDIALOG_H
