#ifndef INDIVSENSRESULTS_H
#define INDIVSENSRESULTS_H

#include <QDialog>
#include <QJsonDocument>
#include <QDialogButtonBox>
#include <QTabWidget>
#include "OMSens/tabs/SensitivityMethodResultsTab.h"

class IndivSensResultsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit IndivSensResultsDialog(QJsonDocument analysisResults, QWidget *pParent = 0);
private:
    // GUI
    SensitivityMethodResultsTab *mpRelativeMethodTab;
    SensitivityMethodResultsTab *mpRMSMethodTab;
    QTabWidget                  *mpTabWidget;
    QDialogButtonBox   *mpButtonBox;
    // Aux
    SensitivityMethodResultsTab* resultsTabForRelativeFromJSONObject(QJsonObject heatmapsJSONObject);
    SensitivityMethodResultsTab* resultsTabForRMSFromJSONObject(QJsonObject heatmapsJSONObject);
    SensitivityMethodResultsTab* resultsTabForMethodFromJSONObject(QString methodJSONName, QJsonObject heatmapsJSONObject, QString description);
signals:

public slots:
};

#endif // INDIVSENSRESULTS_H
