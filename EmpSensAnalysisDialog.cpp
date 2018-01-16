#include "EmpSensAnalysisDialog.h"
#include "utilities.h"
#include <QMessageBox>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>

// BORRAR:
#include <iostream>
// BORRAR^


EmpSensAnalysisDialog::EmpSensAnalysisDialog(QWidget *pParent)
  : QDialog(pParent)
{
    // Model information:
    const QVector<QString> modelVars( QVector<QString>()
                                   << "population"
                                   << "nr_resources"
                                   << "human_welfare_index");
    // Emp Analysis Information:
    const QVector<QString> indices( QVector<QString>()
                                   << "Relative index"
                                   << "Root Mean Square index");
    setWindowTitle("Parameter Sensitivity Analysis - Empirical Indices");
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumWidth(550);
    // set import heading
    mpHeading = Utilities::getHeadingLabel("Empirical Sensitivity Analysis");
    // set separator line
    mpHorizontalLine = Utilities::getHeadingLine();
    // User inputs
    mpPercentageLabel = new Label(tr("Percentage:"));
    mpPercentageBox = new QLineEdit;

    mpVariableLabel = new Label(tr("Variable:"));
    mpVariableComboBox = new QComboBox;
    for (int i_vars=0; i_vars<modelVars.size(); i_vars++)
    {
        mpVariableComboBox->addItem(modelVars[i_vars], QVariant(i_vars));
    }

    mpIndexLabel = new Label(tr("Index:"));
    mpIndexComboBox = new QComboBox;
    for (int i_indices=0; i_indices<indices.size(); i_indices++)
    {
        mpIndexComboBox->addItem(indices[i_indices], QVariant(i_indices));
    }

    mpTimeLabel = new Label(tr("Index:"));
    mpTimeBox = new QLineEdit;


/*    mpBrowseFileButton = new QPushButton(Helper::browse);
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
    mpRunButton = new QPushButton("Ok");
    mpRunButton->setAutoDefault(true);
    connect(mpRunButton, SIGNAL(clicked()), SLOT(runEmpSensAnalysis()));
    // Button quits:
    //connect(mpRunButton, SIGNAL(clicked()),QApplication::instance(), SLOT(quit()));
    // set grid layout
    Label *pNoteLabel = new Label(tr("* This feature is experimental. Most models are not yet handled by it."));
    QGridLayout *pMainLayout = new QGridLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    pMainLayout->addWidget(mpHeading, 0, 0, 1, 3);
    pMainLayout->addWidget(mpHorizontalLine, 1, 0, 1, 3);
    pMainLayout->addWidget(mpPercentageLabel, 2, 0);
    pMainLayout->addWidget(mpPercentageBox, 2, 1);
    pMainLayout->addWidget(mpVariableLabel, 5, 0);
    pMainLayout->addWidget(mpVariableComboBox, 5, 1, 1, 2);
    pMainLayout->addWidget(mpIndexLabel, 6, 0);
    pMainLayout->addWidget(mpIndexComboBox, 6, 1, 1, 2);
    pMainLayout->addWidget(mpTimeLabel, 7, 0);
    pMainLayout->addWidget(mpTimeBox, 7, 1);

/*    pMainLayout->addWidget(mpBrowseFileButton, 2, 2);
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
    pMainLayout->addWidget(mpRunButton, 10, 0, 1, 3, Qt::AlignRight);
    setLayout(pMainLayout);
}

void EmpSensAnalysisDialog::runEmpSensAnalysis()
{
    std::cout << "Values chosen:" << std::endl;
    std::cout << " Percentage: " << mpPercentageBox->text().toUtf8().constData() << std::endl;
    std::cout << " Variable i: " << mpVariableComboBox->currentIndex() << std::endl;
    std::cout << " Index i: " << mpIndexComboBox->currentIndex() << std::endl;
    accept();
}

