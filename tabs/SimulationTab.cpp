#include "SimulationTab.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <limits>
#include <QFormLayout>
#include <QFileDialog>
#include <QLineEdit>


SimulationTab::SimulationTab(QString modelName, QString modelFilePath,
                             double startTime, double stopTime, QString defaultResultsFolderPath,
                             QWidget *pParent) : QWidget(pParent)
{
    // Model name
    mpModelNameLabel = new QLabel(tr("Model:"));
    mpModelNameValue = new QLabel(modelName);
    mpModelNameValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    // Model file path
    mpModelPathLabel = new QLabel(tr("Model file:"));
    mpModelPathValue = new QLabel(modelFilePath);
    mpModelPathValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    // Results dest folder path
    mpDestFolderPathLabel = new QLabel(tr("Analysis results destination folder:"));
    mpDestFolderPathValue = new QLabel(defaultResultsFolderPath);
    mpDestFolderPathValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mpChooseDestFolderButton = new QPushButton("Choose folder");
    mpChooseDestFolderButton->setAutoDefault(true);
    mpChooseDestFolderButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpChooseDestFolderButton, SIGNAL(clicked()), this, SLOT(launchChooseFolderDialog()));

    // Start time
    mpStartTimeLabel = new QLabel(tr("Start time:"));
    mpStartTimeBox = new QDoubleSpinBox;
    mpStartTimeBox->setRange(0, std::numeric_limits<double>::max());
    mpStartTimeBox->setValue(startTime);
    // Stop time
    mpStopTimeLabel = new QLabel(tr("Stop time:"));
    mpStopTimeBox = new QDoubleSpinBox;
    mpStopTimeBox->setRange(0, std::numeric_limits<double>::max());
    mpStopTimeBox->setValue(stopTime);

    // Intermediate results path
    mpIntermediateResultPath = new QLineEdit();
    QLabel *intermediateLabel = new QLabel(tr("Set path to file where to store intermediate results of simulation (*.csv)"));
    mpIntermediateResultPath->setText("/home/omsens/Documents/results_experiments/logging/");

   QFormLayout *mainLayout = new QFormLayout;
   // Model name
   mainLayout->addRow(mpModelNameLabel);
   mainLayout->addRow(mpModelNameValue);
   // Model path
   mainLayout->addRow(mpModelPathLabel);
   mainLayout->addRow(mpModelPathValue);
   // Results dest folder path: Label
   mainLayout->addRow(mpDestFolderPathLabel);
   // Results dest folder path: Value
   QHBoxLayout *pDestFolderRowLayout = new QHBoxLayout;
   pDestFolderRowLayout->addWidget(mpDestFolderPathValue);
   pDestFolderRowLayout->addWidget(mpChooseDestFolderButton);
   mainLayout->addRow(pDestFolderRowLayout);
   // Start time
   mainLayout->addRow(mpStartTimeLabel);
   mainLayout->addRow(mpStartTimeBox);
   // Stop time
   mainLayout->addRow(mpStopTimeLabel);
   mainLayout->addRow(mpStopTimeBox);
   // Intermediate results
   mainLayout->addRow(intermediateLabel);
   mainLayout->addRow(mpIntermediateResultPath);

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

QString SimulationTab::getRestrictionPath() const {
    return mpIntermediateResultPath->text();
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
