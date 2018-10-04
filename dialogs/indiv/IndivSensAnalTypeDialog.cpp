#include "IndivSensAnalTypeDialog.h"
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>

IndivSensAnalTypeDialog::IndivSensAnalTypeDialog(Model *pModel, QWidget *parent) : QDialog(parent)
{

    // Dialog settings
    setMinimumWidth(400);
    // Initialize label
    mpChooseAnalysisLabel = new QLabel("Choose between runnning a predefined analysis for World3 or a new one for the model currently active. ", this);
    // Initialize buttons
    mpRunW3SampleButton    = new QPushButton("Run World3 Analysis Example", this);
    mpRunW3SampleButton->setAutoDefault(true);
    mpRunW3SampleButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mpRunOpenModelButton    = new QPushButton(this);
    mpRunOpenModelButton->setAutoDefault(true);
    mpRunOpenModelButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    // Get model info (if any) for this dialog
    if (pModel == 0)
    {
        // If the pointer is null, there's no currently active model, so disable the button
        QString disabledButtonText = "< No model is currently active >";
        mpRunOpenModelButton->setText(disabledButtonText);
        mpRunOpenModelButton->setEnabled(false);
    }
    else
    {
        // The pointer is not null, so get the model name
        QString modelName = pModel->getModelName();
        QString enabledButtonText = "Run analysis on model: "+modelName;
        mpRunOpenModelButton->setText(enabledButtonText);
        mpRunOpenModelButton->setEnabled(true);
    }


    connect(mpRunW3SampleButton     , &QPushButton::clicked, this, &IndivSensAnalTypeDialog::chooseW3Sample);
    connect(mpRunOpenModelButton    , &QPushButton::clicked, this, &IndivSensAnalTypeDialog::chooseOpenModel);

    // Dialog settings
    setWindowTitle("Choose Analysis Specifications");
    // Layout
    QFormLayout *mainLayout = new QFormLayout(this);
    // Add label
    mainLayout->addWidget(mpChooseAnalysisLabel);
    // Add buttons
    QHBoxLayout *buttonsLayout = new QHBoxLayout(this);
    buttonsLayout->addWidget(mpRunW3SampleButton);
    buttonsLayout->addWidget(mpRunOpenModelButton);
    mainLayout->addRow(buttonsLayout);
    mainLayout->setAlignment(buttonsLayout,Qt::AlignCenter);

    setLayout(mainLayout);
}
void IndivSensAnalTypeDialog::chooseW3Sample()
{
    choseW3InsteadOfOpenModel = true;
    accept();
}

void IndivSensAnalTypeDialog::chooseOpenModel()
{
    choseW3InsteadOfOpenModel = false;
    accept();
}
