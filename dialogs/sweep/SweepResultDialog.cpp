#include "SweepResultDialog.h"

#include <QWidget>
#include <QJsonObject>
#include <QFormLayout>
#include <QPushButton>
#include "dialogs/general/ImageViewerDialog.h"

SweepResultsDialog::SweepResultsDialog(QJsonDocument sweepResults, QWidget *pParent) : QDialog(pParent)
{
    // Parse JSON
    // Get the "main" object of the json document
    QJsonObject sweepResultsObject = sweepResults.object();
    // Get the <var name> to <plot path> mapper
    mVarNameToPlotMap = sweepResultsObject.value(QString("sweep_plots")).toObject();
    // Get the list of variables
    mVariables = mVarNameToPlotMap.keys();

    // Initialize GUI members
    mpVariablesLabel = new QLabel("Plots:");
    mpVariablesComboBox = new QComboBox;
    foreach(const QString& var_name, mVariables) {
        mpVariablesComboBox->addItem(var_name);
    }
    mpOpenPlotButton = new QPushButton("Open");
    mpOpenPlotButton->setAutoDefault(true);
    mpOpenPlotButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpOpenPlotButton, SIGNAL(clicked()), this, SLOT(openSelectedVarPlot()));

    // Dialog settings
    setWindowTitle("Multiparameter sweep result");
    // Layout
    QHBoxLayout *pVarsLayout = new QHBoxLayout;
    pVarsLayout->addWidget(mpVariablesLabel);
    pVarsLayout->addWidget(mpVariablesComboBox);
    pVarsLayout->addWidget(mpOpenPlotButton);
    QFormLayout *mainLayout = new QFormLayout;
    mainLayout->addRow(pVarsLayout);
    // Layout settings
    setLayout(mainLayout);
}

// Slots
void SweepResultsDialog::openSelectedVarPlot()
{
    // Get path
    QString varName = mpVariablesComboBox->currentText();
    QJsonValue varPlotPathJSONValue = mVarNameToPlotMap.value(varName);
    QString varPlotPath = varPlotPathJSONValue.toString();
    // Launch image viewer dialog
    ImageViewerDialog *pImageViewer = new ImageViewerDialog(varPlotPath,this);
    pImageViewer->show();
}
