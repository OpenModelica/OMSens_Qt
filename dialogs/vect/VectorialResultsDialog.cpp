#include "VectorialResultsDialog.h"

#include <QJsonObject>
#include <QStandardItemModel>
#include <QFormLayout>


VectorialResultsDialog::VectorialResultsDialog(QJsonDocument vectorialResults, QString resultsFolderPath, QWidget *pParent) : BaseResultsDialog(pParent)
{
    // Initialize tabs
    mpOptimParamsTab = new OptimizationResultParametersTab(vectorialResults);
    mpOptimOtherTab = new OptimizationResultOtherTab(vectorialResults);
    // Initialize tabs container widget
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpOptimParamsTab, tr("Parameters"));
    mpTabWidget->addTab(mpOptimOtherTab, tr("Other"));

    // GUI: Results folder
    mpResultsFolderPathLabel = new QLabel("Results can be found in:");
    mpResultsFolderPathValue = new QLabel(resultsFolderPath);
    mpResultsFolderPathValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mpResultsFolderPathValue->setTextInteractionFlags(Qt::TextSelectableByMouse);

    // Buttons
    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("Ok", QDialogButtonBox::AcceptRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &VectorialResultsDialog::accept);

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mpTabWidget);
    // Results folder path
    QFormLayout *resultsFolderLayout = new QFormLayout;
    resultsFolderLayout->addRow(mpResultsFolderPathLabel);
    resultsFolderLayout->addRow(mpResultsFolderPathValue);
    mainLayout->addLayout(resultsFolderLayout);

    // Accept button
    mainLayout->addWidget(mpButtonBox);

    // Layout settings
    setLayout(mainLayout);

    // Windows settings
    initializeWindowSettings();
}

void VectorialResultsDialog::initializeWindowSettings()
{
    setMinimumHeight(300);
    setMinimumWidth(450);
    setWindowTitle("Vectorial Analysis Results");
}
