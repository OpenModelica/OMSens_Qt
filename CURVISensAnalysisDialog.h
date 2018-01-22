#ifndef CURVISENSANALYSISDIALOG_H
#define CURVISENSANALYSISDIALOG_H

#include <QDialog>
#include <QFrame>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include "DualLists.h"

class Label;
class CURVISensAnalysisDialog : public QDialog
{
    Q_OBJECT
public:
    CURVISensAnalysisDialog(QWidget *pParent = 0);
    
private:
    Label *mpHeading;
    QFrame *mpHorizontalLine;
    Label *mpLowerBoundLabel;
    QDoubleSpinBox *mpLowerBoundBox;
    Label *mpUpperBoundLabel;
    QDoubleSpinBox *mpUpperBoundBox;
    Label *mpVariableLabel;
    QComboBox *mpVariableComboBox;
    QButtonGroup *mpOptimTypeButtonGroup;
    QRadioButton *mpMaxRadio;
    QRadioButton *mpMinRadio;
    Label *mpParameterLabel;
    DualLists *mpParametersDualLists;
// Remove combobox once duallists is finished
    QComboBox *mpParameterComboBox;
    Label *mpTimeLabel;
    QDoubleSpinBox *mpTimeBox;
    QPushButton *mpRunButton;

    // Aux functions
    void setHeading();
    void initializeWindowSettings();
    void initializeFormInputsAndLabels(const double maxTargetTime, const double maxPerturbationPercentage, const QVector<QString> modelVars, const double defaultTime, const double minPerturbationPercentage, const QVector<QString> modelParams);
    void initializeButton();
    QGridLayout * initializeLayout();
    void addWidgetsToLayout(QGridLayout *pMainLayout);
    void initializeVarForms();
    void initializeVarForms(const QVector<QString> modelVars);
    void initializeParameterForms(const QVector<QString> modelParams);
    void initializeTimeForms(const double defaultTime, const double maxTargetTime);
    void initializeUpperAndLowerBoundsForms(const double minPerturbationPercentage, const double maxPerturbationPercentage);
    
signals:

private slots:
    void runCURVISensAnalysis();
};

#endif // CURVISENSANALYSISDIALOG_H
