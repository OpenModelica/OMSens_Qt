#ifndef PLOTFROMDATADIALOG_H
#define PLOTFROMDATADIALOG_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QComboBox>
#include <QLabel>
#include <QTabWidget>
#include <QDialogButtonBox>

#include "../BaseResultsDialog.h"
#include "../../tabs/sweep_result/SweepResultVariableTab.h"


class PlotFromDataDialog: public BaseResultsDialog
{
    Q_OBJECT
public:
    PlotFromDataDialog(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *pParent = 0);
private:

    QString plot_mPythonBinPath;
    QString plot_mOMSensPath;
    QString plot_mOMSensResultsPath;

    QString plot_specific_experiment;
    QLabel *plot_specific_experiment_label;
    QPushButton *plot_specific_experiment_label_browse_button;

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

    void openPlotsDialog();
    void openHistogramDialog();
    void openScatterplotDialog();

signals:

public slots:
    void setSpecificExperiment();

};

#endif // PLOTFROMDATADIALOG_H
