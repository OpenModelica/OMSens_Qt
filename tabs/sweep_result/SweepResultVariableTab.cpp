#include "SweepResultVariableTab.h"

#include <QVBoxLayout>
#include <QPushButton>

#include "../../dialogs/general/ImageViewerDialog.h"


SweepResultVariableTab::SweepResultVariableTab(QJsonObject varNameToPlotMap, QWidget *pParent) : QDialog(pParent)
{
    // Save map between variable and plot pat
    mVarNameToPlotMap = varNameToPlotMap;

    // Get the list of variables
    mVariables = mVarNameToPlotMap.keys();

    // GUI: plots chooser
    mpVariablesLabel = new QLabel("Plots:");
    mpVariablesComboBox = new QComboBox;
    foreach(const QString& var_name, mVariables) {
        mpVariablesComboBox->addItem(var_name);

    }

    mpOpenPlotButton = new QPushButton("Open");
    mpOpenPlotButton->setAutoDefault(true);
    mpOpenPlotButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpOpenPlotButton, SIGNAL(clicked()), this, SLOT(openSelectedVarPlot()));


    // Layout
    QHBoxLayout *pMainLayout = new QHBoxLayout;
    pMainLayout->addWidget(mpVariablesLabel);
    pMainLayout->addWidget(mpVariablesComboBox);
    pMainLayout->addWidget(mpOpenPlotButton);

    // Layout settings
    setLayout(pMainLayout);
}


// Slots
void SweepResultVariableTab::openSelectedVarPlot()
{
    // Get path
    QString varName = mpVariablesComboBox->currentText();
    QJsonValue varPlotPathJSONValue = mVarNameToPlotMap.value(varName);
    QString varPlotPath = varPlotPathJSONValue.toString();
    // Launch image viewer dialog
    ImageViewerDialog *pImageViewer = new ImageViewerDialog(varPlotPath,this);
    pImageViewer->show();
}
