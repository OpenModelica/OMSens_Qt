#ifndef VECTORIALRESULTSDIALOG_H
#define VECTORIALRESULTSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTabWidget>

#include "../../tabs/optim_result/OptimizationResultParametersTab.h"
#include "../../tabs/optim_result/OptimizationResultOtherTab.h"

class VectorialResultsDialog : public QDialog
{
    Q_OBJECT
public:
    VectorialResultsDialog(QJsonDocument vectorialResults, QWidget *pParent = 0);
private:
    // GUI
    QTabWidget            *mpTabWidget;
    OptimizationResultParametersTab* mpOptimParamsTab;
    OptimizationResultOtherTab*      mpOptimOtherTab;
//    // OLD:
//    // GUI members
//    // x
//    QLabel     *mpXLabel;
//    QTableView *mpXTable;
//    // f(x)
//    QLabel  *mpFxLabel;
//    QLabel  *mpFxValue;
//    // Data members
//    QJsonObject mXOptMap;
//    double mFx;

};

#endif // VECTORIALRESULTSDIALOG_H
