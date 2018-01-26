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
#include "model.h"

class Label;
class CURVISensAnalysisDialog : public QDialog
{
    Q_OBJECT
public:
    CURVISensAnalysisDialog(Model model, QWidget *pParent = 0);
    
private:
    // Model information members
    Model model;
    // GUI members
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
    Label *mpTimeLabel;
    QDoubleSpinBox *mpTimeBox;
    QPushButton *mpRunButton;

    // Aux functions
    void setHeading();
    void initializeWindowSettings();
    void initializeFormInputsAndLabels(const double maxTargetTime, const double maxPerturbationPercentage, const double defaultTime, const double minPerturbationPercentage);
    void initializeButton();
    QGridLayout * initializeLayout();
    void addWidgetsToLayout(QGridLayout *pMainLayout);
    void initializeVarForms();
    void initializeParameterForms();
    void initializeTimeForms(const double defaultTime, const double maxTargetTime);
    void initializeUpperAndLowerBoundsForms(const double minPerturbationPercentage, const double maxPerturbationPercentage);
    
signals:

private slots:
    void runCURVISensAnalysis();
};

#endif // CURVISENSANALYSISDIALOG_H
