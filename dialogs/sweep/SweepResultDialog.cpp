#include "SweepResultDialog.h"

#include <QWidget>
#include <QJsonObject>
#include <QFormLayout>
#include <QPushButton>

SweepResultsDialog::SweepResultsDialog(QJsonDocument sweepResults, QString resultsFolderPath, QWidget *pParent) : BaseResultsDialog(pParent)
{
    // Parse JSON
    // Get the "main" object of the json document
    QJsonObject sweepResultsObject = sweepResults.object();
    // Get the <var name> to <plot path> mapper
    mVarNameToPlotMap = sweepResultsObject.value(QString("sweep_plots")).toObject();

    // Tabs
    mpVariablesResultTab = new SweepResultVariableTab(mVarNameToPlotMap);

    // Tabs container
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpVariablesResultTab, tr("Variables"));

    // Results folder (defined in superclass)
    mpResultsFolderPathLabel = folderPathLabel();
    mpResultsFolderPathValue = folderPathValue(resultsFolderPath);
    // Buttons
    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("Ok", QDialogButtonBox::AcceptRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &SweepResultsDialog::accept);

    // Dialog settings
    setWindowTitle("Multiparameter Sweep Results");
    // Layout
    QFormLayout *mainLayout = new QFormLayout;
    // Tabs group
    mainLayout->addWidget(mpTabWidget);

    // Results folder path
    mainLayout->addRow(mpResultsFolderPathLabel);
    mainLayout->addRow(mpResultsFolderPathValue);

    // Accept button
    mainLayout->addWidget(mpButtonBox);

    // Layout settings
    setLayout(mainLayout);
}
