#ifndef EMPSENSANALYSISDIALOG_H
#define EMPSENSANALYSISDIALOG_H
#include <QDialog>
#include <QFrame>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>

class Label;
class EmpSensAnalysisDialog : public QDialog
{
    Q_OBJECT
public:
    EmpSensAnalysisDialog(QWidget *pParent = 0);
private:
    Label *mpHeading;
    QFrame *mpHorizontalLine;
    Label *mpPercentageLabel;
    QDoubleSpinBox *mpPercentageBox;
    Label *mpVariableLabel;
    QComboBox *mpVariableComboBox;
    Label *mpIndexLabel;
    QComboBox *mpIndexComboBox;
    QPushButton *mpRunButton;
    Label *mpTimeLabel;
    QDoubleSpinBox *mpTimeBox;

private slots:
  void runEmpSensAnalysis();
};

#endif // EMPSENSANALYSISDIALOG_H
