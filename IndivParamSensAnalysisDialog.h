#ifndef INDIVPARAMSENSANALYSISDIALOG_H
#define INDIVPARAMSENSANALYSISDIALOG_H
#include "model.h"
#include <QDialog>
#include <QFrame>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGridLayout>

class Label;
class IndivParamSensAnalysisDialog : public QDialog
{
    Q_OBJECT
public:
    IndivParamSensAnalysisDialog(Model model, QWidget *pParent = 0);

private:
    // Model information members
    Model model;
    // GUI members
    Label *mpHeading;
    QFrame *mpHorizontalLine;
    Label *mpPercentageLabel;
    QDoubleSpinBox *mpPercentageBox;
    Label *mpVariableLabel;
    QComboBox *mpVariableComboBox;
    Label *mpMethodLabel;
    QButtonGroup *mpMethodsButtonGroup;
    QRadioButton *mpRelRadio;
    QRadioButton *mpRMSRadio;
    QPushButton *mpRunButton;
    Label *mpTimeLabel;
    QDoubleSpinBox *mpTimeBox;

    void initializeWindowSettings();

    void setHeading();

    void initializeFormInputsAndLabels(const double min_perturbation_perc, const double max_perturbation_perc, const double max_target_time, const QVector<QString> methods);

    void initializeButton();

    void addWidgetsToLayout(QGridLayout *pMainLayout);

    QGridLayout * initializeLayout();

private slots:
  void runIndivParamSensAnalysis();
};

#endif // INDIVPARAMSENSANALYSISDIALOG_H
