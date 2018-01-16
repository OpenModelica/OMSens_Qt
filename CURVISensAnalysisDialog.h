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

class Label;
class CURVISensAnalysisDialog : public QDialog
{
    Q_OBJECT
public:
    CURVISensAnalysisDialog(QWidget *pParent = 0);
private:
    Label *mpHeading;
    QFrame *mpHorizontalLine;
    Label *mpPercentageLabel;
    QDoubleSpinBox *mpPercentageBox;
    Label *mpVariableLabel;
    QComboBox *mpVariableComboBox;
    Label *mpIndexLabel;
    QButtonGroup *mpOptimTypeButtonGroup;
    QRadioButton *mpMaxRadio;
    QRadioButton *mpMinRadio;
    QVBoxLayout *mpOptimRadioLayout;
    QPushButton *mpRunButton;
    Label *mpTimeLabel;
    QDoubleSpinBox *mpTimeBox;

signals:

private slots:
    void runCURVISensAnalysis();
};

#endif // CURVISENSANALYSISDIALOG_H
