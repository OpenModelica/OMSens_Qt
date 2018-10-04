#include "ParametersSimpleTab.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QHeaderView>
#include <QLabel>
#include <QCheckBox>
#include <QFormLayout>

ParametersSimpleTab::ParametersSimpleTab(QList<QString> parameters, double percentage, QWidget *parent) : QWidget(parent)
{
    // Initialize label with brief description of the analysis
    mpBriefDescriptionLabel = new QLabel("Each selected parameter is perturbed in isolation, one at a time",this);

    // Percentage
    mpPercentageLabel = new QLabel(tr("Percentage (+ or -):"));
    mpPercentageBox = new QDoubleSpinBox;
    mpPercentageBox->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    mpPercentageBox->setValue(percentage);
    mpPercentageBox->setSuffix("%");

    //Initialize table header
    mpParametersTable = new QTableWidget(0, 2);
    const QList<QString> tableHeaders( QList<QString>()
                                     << "Parameter"
                                     << "Perturb?"
                                     );
    mpParametersTable->setHorizontalHeaderLabels(tableHeaders);
    // Declare the QPair outside the foreach because the commas are ambigous for Qt's macro
    foreach (QString param_name, parameters)
    {
        // Add a row
        // Row index to add row to
        const int rowNum = mpParametersTable->rowCount();
        // Add "blank" row
        mpParametersTable->insertRow(rowNum);
        // Fill blank row with values corresponding to this variable
        // Set parameter name
        QLabel *paramNameWidget = new QLabel(param_name);
        mpParametersTable->setCellWidget(rowNum,paramColPos, paramNameWidget);
        // Set checkbox
        QCheckBox *includeCheckBox = new QCheckBox;
        includeCheckBox->setChecked(true);
        mpParametersTable->setCellWidget(rowNum,cboxColPos,includeCheckBox);
    }
    // Set table settings
    // Resize columns to contents
    mpParametersTable->resizeColumnsToContents();

    QFormLayout *mainLayout = new QFormLayout;
    // Percentage
    QHBoxLayout *pHorizontalSubLayout = new QHBoxLayout;
    pHorizontalSubLayout->addWidget(mpPercentageLabel);
    pHorizontalSubLayout->addWidget(mpPercentageBox);
    mainLayout->addRow(pHorizontalSubLayout);
    // Parameters table/list
    mainLayout->addRow(mpParametersTable);
    // Description
    mainLayout->addRow(mpBriefDescriptionLabel);
    setLayout(mainLayout);
}

QTableWidget *ParametersSimpleTab::getParametersTable() const
{
    return mpParametersTable;
}

// Getters
double ParametersSimpleTab::getPercentageValue() const
{
    return mpPercentageBox->value();
}
