#ifndef INDIVPARAMSENSANALYSISDIALOG_H
#define INDIVPARAMSENSANALYSISDIALOG_H
#include "../../model.h"
#include "../../tabs/VariablesTab.h"
#include "../../tabs/ParametersSimpleTab.h"
#include "../../tabs/SimulationTab.h"
#include "../../tabs/HelpTab.h"
#include "../BaseRunSpecsDialog.h"

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
    IndivParamSensAnalysisDialog(QJsonDocument jsonSpecsDocument, QWidget *pParent = 0);
    IndivParamSensAnalysisDialog(Model model, QWidget *pParent = 0);

    // Getters
    QJsonObject getRunSpecifications() const;
    QString getDestFolderPath() const;



private:
    // GUI members
    QTabWidget          *mpTabWidget;
    SimulationTab       *mpSimulationSettingsTab;
    VariablesTab        *mpVariablesTab;
    ParametersSimpleTab *mpParametersTab;
    HelpTab             *mpHelpTab;
    QDialogButtonBox    *mpButtonBox;
    // Dialog "return" members
    QJsonObject mRunSpecifications;
    QString     destFolderPath;

    // Conventions
    QString helpTextPath = ":/OMSens/indiv/help.html";

    // Auxs
    void initializeDialogWithData(QList<QString> variables, QList<QString> parameters, QString modelName, QString modelFilePath, double percentage, double startTime, double stopTime);
    void initializeWindowSettings();
    void setHeading();
    void initializeFormInputsAndLabels(const double min_perturbation_perc, const double max_perturbation_perc, const double max_target_time, const QVector<QString> methods);
    void initializeButton();
    void addWidgetsToLayout(QGridLayout *pMainLayout);
    QGridLayout * initializeLayout();
    QList<QString> fromListOfVariantToListOfStr(QList<QVariant> listOfQVariant);
    QString readHelpText();

private slots:
  void runIndivParamSensAnalysis();
};

#endif // INDIVPARAMSENSANALYSISDIALOG_H
