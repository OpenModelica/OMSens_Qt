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
#include "../BaseRunSpecsDialog.h"

class VectorialSensAnalysisDialog : public BaseRunSpecsDialog
{
    Q_OBJECT
public:
    // Constructors
    VectorialSensAnalysisDialog(Model model, QWidget *pParent = 0);
    // Getters
    QJsonDocument getRunSpecifications() const;
    QString getDestFolderPath() const;
    // Conventions
    QString pythonScriptName();

private:
    void initialize(QList<QString> variables, QList<ParameterInclusion> params_inclusion, QString modelName, QString modelFilePath, double percentage, double startTime, double stopTime);
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

    // Conventions
    QString helpTextPath = ":/OMSens/vect/help.html";

    // Aux functions
    void initializeWindowSettings();
    QString readHelpText();

    QList<ParameterInclusion> defaultParametersToInclude(QList<QString> parameters);
    
private slots:
    void runVectorialParamSensAnalysis();
};

#endif // VECTORIALPARAMSENSANALYSISDIALOG_H
