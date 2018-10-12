#include "VectorialResultsDialog.h"

#include <QJsonObject>
#include <QStandardItemModel>
#include <QFormLayout>


VectorialResultsDialog::VectorialResultsDialog(QJsonDocument vectorialResults, QWidget *pParent) : BaseResultsDialog(pParent)
{
    // Initialize tabs
    mpOptimParamsTab = new OptimizationResultParametersTab(vectorialResults);
    mpOptimOtherTab = new OptimizationResultOtherTab(vectorialResults);
    // Initialize tabs container widget
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpOptimParamsTab, tr("Parameters"));
    mpTabWidget->addTab(mpOptimOtherTab, tr("Other"));

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mpTabWidget);
    setLayout(mainLayout);

    // Windows settings
    this->setMinimumHeight(600);
    this->setMinimumWidth(450);
}
