#ifndef SWEEPRESULTDIALOG_H
#define SWEEPRESULTDIALOG_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QComboBox>
#include <QLabel>
#include <QTabWidget>
#include <QDialogButtonBox>

#include "../BaseResultsDialog.h"
#include "../../tabs/sweep_result/SweepResultVariableTab.h"


class SweepResultsDialog: public BaseResultsDialog
{
    Q_OBJECT
public:
    SweepResultsDialog(QJsonDocument sweepResults, QString resultsFolderPath, QWidget *pParent = 0);
private:
    // GUI
    QTabWidget *mpTabWidget;
    SweepResultVariableTab *mpVariablesResultTab;
    QLabel      *mpResultsFolderPathLabel;
    QLabel      *mpResultsFolderPathValue;
    QDialogButtonBox   *mpButtonBox;
    // Data members
    QJsonObject mVarNameToPlotMap;
    QList<QString> mVariables;

};

#endif // SWEEPRESULTDIALOG_H
