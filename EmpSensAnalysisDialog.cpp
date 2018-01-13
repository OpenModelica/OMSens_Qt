#include "EmpSensAnalysisDialog.h"
#include "utilities.h"
#include <QMessageBox>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>



EmpSensAnalysisDialog::EmpSensAnalysisDialog(QWidget *pParent)
  : QDialog(pParent)
{
    //setWindowTitle(QString(Helper::applicationName).append(" - ").append(Helper::importFMU));
    setWindowTitle("Win Title");
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumWidth(550);
    // set import heading
    //mpImportFMUHeading = Utilities::getHeadingLabel(Helper::importFMU);
    mpImportFMUHeading = Utilities::getHeadingLabel("Empirical Sensitivity Analysis");
    // set separator line
    mpHorizontalLine = Utilities::getHeadingLine();
    // create FMU File selection controls
    mpFmuFileLabel = new Label(tr("FMU File:"));
/*
    mpFmuFileTextBox = new QLineEdit;
    mpBrowseFileButton = new QPushButton(Helper::browse);
    mpBrowseFileButton->setAutoDefault(false);
    connect(mpBrowseFileButton, SIGNAL(clicked()), SLOT(setSelectedFile()));
    // create Output Directory selection controls
    mpOutputDirectoryLabel = new Label(tr("Output Directory (Optional):"));
    mpOutputDirectoryTextBox = new QLineEdit;
    mpBrowseDirectoryButton = new QPushButton(Helper::browse);
    mpBrowseDirectoryButton->setAutoDefault(false);
    connect(mpBrowseDirectoryButton, SIGNAL(clicked()), SLOT(setSelectedDirectory()));
    // create Log Level Drop Down
    mpLogLevelLabel = new Label(tr("Log Level:"));
    mpLogLevelComboBox = new QComboBox;
    mpLogLevelComboBox->addItem(tr("Nothing"), QVariant(0));
    mpLogLevelComboBox->addItem(tr("Fatal"), QVariant(1));
    mpLogLevelComboBox->addItem(tr("Error"), QVariant(2));
    mpLogLevelComboBox->addItem(tr("Warning"), QVariant(3));
    mpLogLevelComboBox->addItem(Helper::information, QVariant(4));
    mpLogLevelComboBox->addItem(tr("Verbose"), QVariant(5));
    mpLogLevelComboBox->addItem(tr("Debug"), QVariant(6));
    mpLogLevelComboBox->setCurrentIndex(3);
    // create debug logging checkbox
    mpDebugLoggingCheckBox = new QCheckBox(tr("Debug Logging"));
    // create generate input connectors pins checkbox
    mpGenerateIntputConnectors = new QCheckBox(tr("Generate input connector pins"));
    mpGenerateIntputConnectors->setChecked(true);
    // create generate output connectors pins checkbox
    mpGenerateOutputConnectors = new QCheckBox(tr("Generate output connector pins"));
    mpGenerateOutputConnectors->setChecked(true);
    // import FMU note
    mpOutputDirectoryNoteLabel = new Label(tr("* If no Output Directory specified then the FMU files are generated in the current working directory."));
*/
    // create OK button
    mpImportButton = new QPushButton("Ok");
    mpImportButton->setAutoDefault(true);
    //connect(mpImportButton, SIGNAL(clicked()), SLOT(importFMU()));
    // set grid layout
    Label *pNoteLabel = new Label(tr("* This feature is experimental. Most models are not yet handled by it."));
    QGridLayout *pMainLayout = new QGridLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    pMainLayout->addWidget(mpImportFMUHeading, 0, 0, 1, 3);
    pMainLayout->addWidget(mpHorizontalLine, 1, 0, 1, 3);
    pMainLayout->addWidget(mpFmuFileLabel, 2, 0);
/*
    pMainLayout->addWidget(mpFmuFileTextBox, 2, 1);
    pMainLayout->addWidget(mpBrowseFileButton, 2, 2);
    pMainLayout->addWidget(mpOutputDirectoryLabel, 3, 0);
    pMainLayout->addWidget(mpOutputDirectoryTextBox, 3, 1);
    pMainLayout->addWidget(mpBrowseDirectoryButton, 3, 2);
    pMainLayout->addWidget(mpOutputDirectoryNoteLabel, 4, 0, 1, 3, Qt::AlignLeft);
    pMainLayout->addWidget(mpLogLevelLabel, 5, 0);
    pMainLayout->addWidget(mpLogLevelComboBox, 5, 1, 1, 2);
    pMainLayout->addWidget(mpDebugLoggingCheckBox, 6, 0, 1, 3);
    pMainLayout->addWidget(mpGenerateIntputConnectors, 7, 0, 1, 3);
    pMainLayout->addWidget(mpGenerateOutputConnectors, 8, 0, 1, 3);
    pMainLayout->addWidget(pNoteLabel, 9, 0, 1, 3, Qt::AlignLeft);
*/
    pMainLayout->addWidget(mpImportButton, 10, 0, 1, 3, Qt::AlignRight);
    setLayout(pMainLayout);
}
