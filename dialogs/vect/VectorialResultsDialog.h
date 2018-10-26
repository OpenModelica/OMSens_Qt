#ifndef VECTORIALRESULTSDIALOG_H
#define VECTORIALRESULTSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTabWidget>
#include <QDialogButtonBox>

#include "../../tabs/optim_result/OptimizationResultParametersTab.h"
#include "../../tabs/optim_result/OptimizationResultOtherTab.h"
#include "../BaseResultsDialog.h"

class VectorialResultsDialog : public BaseResultsDialog
{
    Q_OBJECT
public:
    VectorialResultsDialog(QJsonDocument vectorialResults, QString resultsFolderPath, QWidget *pParent = 0);
private:
    // GUI
    QTabWidget            *mpTabWidget;
    OptimizationResultParametersTab* mpOptimParamsTab;
    OptimizationResultOtherTab*      mpOptimOtherTab;
    QLabel      *mpResultsFolderPathLabel;
    QLabel      *mpResultsFolderPathValue;
    QDialogButtonBox   *mpButtonBox;
    // Plot
    QLabel      *mpFxPlotLabel;
    QPushButton *mpOpenPlotButton;
    // stoptime
    QLabel *mpStopTimeLabel;
    QLabel *mpStopTimeValue;
    // Data
    double mStopTime;
    QString mPlotPath;

    // Aux functions
    void initializeWindowSettings();

private slots:
    void openPlot();
};

#endif // VECTORIALRESULTSDIALOG_H
