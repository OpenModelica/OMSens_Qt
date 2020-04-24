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
    mpResultsFolderPathLabel  = resultsFolderLabel();
    mpResultsFolderPathValue  = resultsFolderPathLabel(resultsFolderPath);
    mpOpenResultsFolderButton = buttonToOpenResultsFolder();


    // Buttons
    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("Ok", QDialogButtonBox::AcceptRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &SweepResultsDialog::accept);

    // Dialog settings
    setWindowTitle("Multiparameter Sweep Results");
    // Layout
    QVBoxLayout *pMainLayout = new QVBoxLayout;

    // Tabs group
    pMainLayout->addWidget(mpTabWidget);

    // Results folder path
    QGridLayout *resultsFolderLayout = new QGridLayout;
    resultsFolderLayout->addWidget(mpResultsFolderPathLabel, 0, 0);
    resultsFolderLayout->addWidget(mpResultsFolderPathValue, 1, 0);
    resultsFolderLayout->addWidget(mpOpenResultsFolderButton, 1, 1);
    pMainLayout->addLayout(resultsFolderLayout);

    // Accept button
    pMainLayout->addWidget(mpButtonBox, 0, Qt::AlignCenter);

    // Layout settings
    setLayout(pMainLayout);
}
