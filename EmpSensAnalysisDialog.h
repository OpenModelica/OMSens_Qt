#ifndef EMPSENSANALYSISDIALOG_H
#define EMPSENSANALYSISDIALOG_H
#include <QDialog>
#include <QFrame>
#include <QLineEdit>
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
    QLineEdit *mpPercentageBox;
    Label *mpVariableLabel;
    QComboBox *mpVariableComboBox;
    Label *mpIndexLabel;
    QComboBox *mpIndexComboBox;
    QPushButton *mpRunButton;

/*    QPushButton *mpBrowseFileButton;
    Label *mpOutputDirectoryLabel;
    QLineEdit *mpOutputDirectoryTextBox;
    QPushButton *mpBrowseDirectoryButton;
    Label *mpLogLevelLabel;
    QComboBox *mpLogLevelComboBox;
    QCheckBox *mpDebugLoggingCheckBox;
    QCheckBox *mpGenerateIntputConnectors;
    QCheckBox *mpGenerateOutputConnectors;
    Label *mpOutputDirectoryNoteLabel;
    QPushButton *mpImportButton;
*/

private slots:
  void runEmpSensAnalysis();
/*
  void setSelectedFile();
  void setSelectedDirectory();
  void importFMU();
*/
};

#endif // EMPSENSANALYSISDIALOG_H
