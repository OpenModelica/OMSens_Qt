#ifndef EMPSENSANALYSISDIALOG_H
#define EMPSENSANALYSISDIALOG_H
#include <QDialog>
#include <QFrame>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGridLayout>

class Label;
class EmpSensAnalysisDialog : public QDialog
{
    Q_OBJECT
public:
    EmpSensAnalysisDialog(QVector<QString> modelVars, QWidget *pParent = 0);

private:
    // Model information members
    QVector<QString> modelVars;
    // GUI members
    Label *mpHeading;
    QFrame *mpHorizontalLine;
    Label *mpPercentageLabel;
    QDoubleSpinBox *mpPercentageBox;
    Label *mpVariableLabel;
    QComboBox *mpVariableComboBox;
    Label *mpIndexLabel;
    QButtonGroup *mpIndicesButtonGoup;
    QRadioButton *mpRelRadio;
    QRadioButton *mpRMSRadio;
    QPushButton *mpRunButton;
    Label *mpTimeLabel;
    QDoubleSpinBox *mpTimeBox;

    void initializeWindowSettings();

    void setHeading();

    void initializeFormInputsAndLabels(const double min_perturbation_perc, const QVector<QString> modelVars, const double max_perturbation_perc, const double max_target_time);

    void initializeButton();

    void addWidgetsToLayout(QGridLayout *pMainLayout);

    QGridLayout * initializeLayout();

private slots:
  void runEmpSensAnalysis();
};

#endif // EMPSENSANALYSISDIALOG_H
