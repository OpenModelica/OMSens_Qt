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
    QComboBox *mpParameterComboBox;
    Label *mpTimeLabel;
    QDoubleSpinBox *mpTimeBox;
    QPushButton *mpRunButton;

signals:

private slots:
    void runCURVISensAnalysis();
};

#endif // CURVISENSANALYSISDIALOG_H
