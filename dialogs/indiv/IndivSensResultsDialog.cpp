#include "IndivSensResultsDialog.h"

#include <QJsonObject>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>

IndivSensResultsDialog::IndivSensResultsDialog(QJsonDocument analysisResults, QString resultsFolderPath, QWidget *pParent) : BaseResultsDialog(pParent)
{
    // Parse JSON
    // Get the "main" object of the json document
    QJsonObject analysisResultsObject = analysisResults.object();
    // Get the heatmaps object
    QJsonObject heatmapsJSONObject = analysisResultsObject.value(QString("heatmaps")).toObject();
    // Get the heatmap path for a sensitivity method


    // Initialize tabs depending on the method type
    mpRelativeMethodTab = resultsTabForRelativeFromJSONObject(heatmapsJSONObject);
    mpRMSMethodTab      = resultsTabForRMSFromJSONObject(heatmapsJSONObject);
    // Initialize tabs container widget
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpRelativeMethodTab, tr("Relative (REL)"));
    mpTabWidget->addTab(mpRMSMethodTab      , tr("Root Mean Square (RMS)"));
    //Buttons
    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("Ok", QDialogButtonBox::AcceptRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &IndivSensResultsDialog::accept);

    // Results folder (defined in superclass)
    mpResultsFolderPathLabel  = resultsFolderLabel();
    mpResultsFolderPathValue  = resultsFolderPathLabel(resultsFolderPath);
    mpOpenResultsFolderButton = buttonToOpenResultsFolder();

    // Dialog settings
    setWindowTitle("Individual Sensitivity Analysis Results");
    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    // Tabs widget
    mainLayout->addWidget(mpTabWidget);
    // Add results folder
    QGridLayout *resultsFolderLayout = new QGridLayout;
    resultsFolderLayout->addWidget(mpResultsFolderPathLabel, 0, 0);
    resultsFolderLayout->addWidget(mpResultsFolderPathValue, 1, 0);
    resultsFolderLayout->addWidget(mpOpenResultsFolderButton, 1, 1);
    mainLayout->addLayout(resultsFolderLayout);
    // Accept button
    mainLayout->addWidget(mpButtonBox, 0, Qt::AlignCenter);

    // Layout settings
    setLayout(mainLayout);
}

// Auxs
SensitivityMethodResultsTab* IndivSensResultsDialog::resultsTabForRelativeFromJSONObject(QJsonObject heatmapsJSONObject)
{
    QString methodJSONName = "Relative";
    QString description = "The REL index calculates the change of a state variable (at the end of a simulation)\n"
                          "with and without a parameter perturbation (at the beginning of the simulation).\n"
                          "It can be used to rank parameters according to their impact on a state variable at a target final time.";
    SensitivityMethodResultsTab *pResultsTab = resultsTabForMethodFromJSONObject(methodJSONName, heatmapsJSONObject, description);
    return pResultsTab;
}
SensitivityMethodResultsTab* IndivSensResultsDialog::resultsTabForRMSFromJSONObject(QJsonObject heatmapsJSONObject)
{
    QString methodJSONName = "RMS";
    QString description = "The RMS index calculates the Root Mean Square of the differences between the values assumed\n"
                          "by a state variable (along the whole simulation) with and without a parameter perturbation.\n"
                          "It can be used to rank parameters according to their accumulated impact on a state variable\n"
                          "throughout the simulation time.";
    SensitivityMethodResultsTab *pResultsTab = resultsTabForMethodFromJSONObject(methodJSONName, heatmapsJSONObject, description);
    return pResultsTab;
}

SensitivityMethodResultsTab* IndivSensResultsDialog::resultsTabForMethodFromJSONObject(QString methodJSONName, QJsonObject heatmapsJSONObject, QString description)
{
    // Get heatmap info
    QJsonObject methodHeatmapsJSONObject = heatmapsJSONObject.value(methodJSONName).toObject();
    QString     matrixPath               = methodHeatmapsJSONObject.value(QString("matrix_file_path")).toString();
    QString     heatmapPath              = methodHeatmapsJSONObject.value(QString("plot_path")).toString();
    QString     rowsIDsPath              = methodHeatmapsJSONObject.value(QString("index_mapping_file_path")).toString();
    QString     columnsIDsPath           = methodHeatmapsJSONObject.value(QString("cols_mapping_file_path")).toString();
    SensitivityMethodResultsTab *pResultsTab = new SensitivityMethodResultsTab(description, matrixPath, heatmapPath, columnsIDsPath, rowsIDsPath);
    return pResultsTab;
}
