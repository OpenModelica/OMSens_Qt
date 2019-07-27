#ifndef SWEEPFROMDATADIALOG_H
#define SWEEPFROMDATADIALOG_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QComboBox>
#include <QLabel>
#include <QTabWidget>
#include <QDialogButtonBox>

#include "../BaseResultsDialog.h"
#include "../../tabs/sweep_result/SweepResultVariableTab.h"


class SweepFromDataDialog: public BaseResultsDialog
{
    Q_OBJECT
public:
    SweepFromDataDialog(QWidget *pParent = 0);
private:
    // GUI (there are some components defined in the superclass)
    QTabWidget *mpTabWidget;
    SweepResultVariableTab *mpVariablesResultTab;
    QDialogButtonBox   *mpButtonBox;
    // Data members
    QJsonObject mVarNameToPlotMap;
    QList<QString> mVariables;

    QString progressDialogTextForCurrentTime();

    QString mPythonScriptLibraryPath;
    QString mPythonScriptPath;
    QString defaultResultsFolderPath;

    int makeHistogram();

};

#endif // SWEEPFROMDATADIALOG_H
