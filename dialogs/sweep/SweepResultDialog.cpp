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

    // Initialize tabs
    QString defaultResultsFolderPath = "/home/omsens/Documents/sweep_results";
    mpVariablesResultTab = new SweepResultVariableTab(mVarNameToPlotMap);

    // Initialize tabs container widget
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpVariablesResultTab, tr("Variables"));

//    // Get the list of variables
//    mVariables = mVarNameToPlotMap.keys();

//    // GUI: plots chooser
//    mpVariablesLabel = new QLabel("Plots:");
//    mpVariablesComboBox = new QComboBox;
//    foreach(const QString& var_name, mVariables) {
//        mpVariablesComboBox->addItem(var_name);
//    }
//    mpOpenPlotButton = new QPushButton("Open");
//    mpOpenPlotButton->setAutoDefault(true);
//    mpOpenPlotButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    connect(mpOpenPlotButton, SIGNAL(clicked()), this, SLOT(openSelectedVarPlot()));
    // GUI: Results folder
    mpResultsFolderPathLabel = new QLabel("Results can be found in:");
    mpResultsFolderPathValue = new QLabel(resultsFolderPath);
    mpResultsFolderPathValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mpResultsFolderPathValue->setTextInteractionFlags(Qt::TextSelectableByMouse);

    // Dialog settings
    setWindowTitle("Multiparameter sweep result");
    // Layout
    QFormLayout *mainLayout = new QFormLayout;
    // Tabs group
    mainLayout->addWidget(mpTabWidget);
//    QHBoxLayout *pVarsLayout = new QHBoxLayout;
//    pVarsLayout->addWidget(mpVariablesLabel);
//    pVarsLayout->addWidget(mpVariablesComboBox);
//    pVarsLayout->addWidget(mpOpenPlotButton);
//    mainLayout->addRow(pVarsLayout);

    mainLayout->addRow(mpResultsFolderPathLabel);
    mainLayout->addRow(mpResultsFolderPathValue);

    // Layout settings
    setLayout(mainLayout);
}

// Slots
// void SweepResultsDialog::openSelectedVarPlot()
// {
//     // Get path
//     QString varName = mpVariablesComboBox->currentText();
//     QJsonValue varPlotPathJSONValue = mVarNameToPlotMap.value(varName);
//     QString varPlotPath = varPlotPathJSONValue.toString();
//     // Launch image viewer dialog
//     ImageViewerDialog *pImageViewer = new ImageViewerDialog(varPlotPath,this);
//     pImageViewer->show();
// }
