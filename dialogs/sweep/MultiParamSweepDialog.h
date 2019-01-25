#ifndef MULTIPARAMSWEEPDIALOG_H
#define MULTIPARAMSWEEPDIALOG_H


#include <QDialog>
#include <QDoubleSpinBox>
#include <QFrame>
#include <QGridLayout>
#include <QTableWidget>
#include <QDialogButtonBox>
#include <QJsonObject>
#include <QString>
#include "../../tabs/SimulationTab.h"
#include "../../tabs/VariablesTab.h"
#include "../../tabs/ParametersExtendedTab.h"
#include "../../tabs/HelpTab.h"
#include "../../DualLists.h"
#include "../../model.h"
#include "../BaseRunSpecsDialog.h"

class MultiParamSweepDialog : public BaseRunSpecsDialog
{
    Q_OBJECT
public:
    // Constructors
    MultiParamSweepDialog(Model model, QWidget *pParent = 0);

    // Getters
    QJsonDocument getRunSpecifications() const;
    QString getDestFolderPath() const;

    // Conventions
    QString pythonScriptName();

private:
    void initializeDialogWithData(QList<QString> variables, QList<QString> parameters, QString modelName, QString modelFilePath, double startTime, double stopTime);
    // GUI members
    QTabWidget            *mpTabWidget;
    SimulationTab         *mpSimulationSettingsTab;
    VariablesTab          *mpVariablesTab;
    ParametersExtendedTab *mpParametersTab;
    HelpTab               *mpHelpTab;
    QDialogButtonBox    *mpButtonBox;
    // Dialog "return" members
    QJsonObject mRunSpecifications;
    QString     mpDestFolderPath;

    // Conventions
    QString helpTextPath = ":/OMSens/sweep/help.html";

    // Auxs:
    void initializeWindowSettings();
    QString readHelpText();

private slots:
    void runMultiParamSweep();
};

#endif // MULTIPARAMSWEEPDIALOG_H
