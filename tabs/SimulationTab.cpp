#include "SimulationTab.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <limits>
#include <QFormLayout>
#include <QFileDialog>


SimulationTab::SimulationTab(QString modelName, QString modelFilePath, double startTime, double stopTime, QString defaultResultsFolderPath, QWidget *pParent) : QWidget(pParent)
{
    // Model name
    mpModelNameLabel = new QLabel(tr("Model:"), this);
    mpModelNameValue = new QLabel(modelName, this);
    mpModelNameValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    // Model file path
    mpModelPathLabel = new QLabel(tr("Model file:"), this);
    mpModelPathValue = new QLabel(modelFilePath);
    mpModelPathValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    // Results dest folder path
    mpDestFolderPathLabel = new QLabel(tr("Analysis results destination folder:"), this);
    mpDestFolderPathValue = new QLabel(defaultResultsFolderPath, this);
    mpDestFolderPathValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mpChooseDestFolderButton = new QPushButton("Choose folder", this);
    mpChooseDestFolderButton->setAutoDefault(true);
    mpChooseDestFolderButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpChooseDestFolderButton, SIGNAL(clicked()), this, SLOT(launchChooseFolderDialog()));

    // Start time
    mpStartTimeLabel = new QLabel(tr("Start time:"), this);
    mpStartTimeBox = new QDoubleSpinBox(this);
    mpStartTimeBox->setRange(0, std::numeric_limits<double>::max());
    mpStartTimeBox->setValue(startTime);
    // Stop time
    mpStopTimeLabel = new QLabel(tr("Stop time:"), this);
    mpStopTimeBox = new QDoubleSpinBox(this);
    mpStopTimeBox->setRange(0, std::numeric_limits<double>::max());
    mpStopTimeBox->setValue(stopTime);

   QFormLayout *mainLayout = new QFormLayout(this);
   // Model name
   mainLayout->addRow(mpModelNameLabel);
   mainLayout->addRow(mpModelNameValue);
   // Model path
   mainLayout->addRow(mpModelPathLabel);
   mainLayout->addRow(mpModelPathValue);
   // Results dest folder path: Label
   mainLayout->addRow(mpDestFolderPathLabel);
   // Results dest folder path: Value
   QHBoxLayout *pDestFolderRowLayout = new QHBoxLayout(this);
   pDestFolderRowLayout->addWidget(mpDestFolderPathValue);
   pDestFolderRowLayout->addWidget(mpChooseDestFolderButton);
   mainLayout->addRow(pDestFolderRowLayout);
   // Start time
   mainLayout->addRow(mpStartTimeLabel);
   mainLayout->addRow(mpStartTimeBox);
   // Stop time
   mainLayout->addRow(mpStopTimeLabel);
   mainLayout->addRow(mpStopTimeBox);

   // Layout settings
   setLayout(mainLayout);
}
// Slots
void SimulationTab::launchChooseFolderDialog()
{
    // Launch dialog
    QString destFolderPath = QFileDialog::getExistingDirectory(this, tr("Choose Destination Folder"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    // Save path into member variable
    mpDestFolderPathValue->setText(destFolderPath);
}


double SimulationTab::getStartTimeValue() const
{

    return mpStartTimeBox->value();
}

double SimulationTab::getStopTimeValue() const
{
    return mpStopTimeBox->value();
}

QString SimulationTab::getDestFolderPath() const
{
    return mpDestFolderPathValue->text();
}

QString SimulationTab::getModelName() const
{
    return mpModelNameValue->text();
}

QString SimulationTab::getModelPath() const
{
    return mpModelPathValue->text();
}
