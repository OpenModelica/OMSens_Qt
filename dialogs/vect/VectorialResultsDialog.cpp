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

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mpTabWidget);
    // Add results folder
    QFormLayout *resultsFolderLayout = new QFormLayout;
    resultsFolderLayout->addRow(mpResultsFolderPathLabel);
    resultsFolderLayout->addRow(mpResultsFolderPathValue);
    mainLayout->addLayout(resultsFolderLayout);

    // Layout settings
    setLayout(mainLayout);

    // Windows settings
    this->setMinimumHeight(300);
    this->setMinimumWidth(450);
}
