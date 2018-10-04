#include "ParametersExtendedTab.h"

#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QFormLayout>


ParametersExtendedTab::ParametersExtendedTab(QList<QString> parameters, QWidget *parent) : QWidget(parent)
{
    // Initialize label with brief description of the sweep
    mpBriefDescriptionLabel = new QLabel("The total #iterations will be the product of the #iterations of all the parameters.");
    //Initialize table header
    mpParametersTable = new QTableWidget(0, 4);
    const QList<QString> tableHeaders( QList<QString>()
                                     << "Parameter"
                                     << "#iter"
                                     << "perturbation"
                                     << "Perturb?"
                                     );
    mpParametersTable->setHorizontalHeaderLabels(tableHeaders);
    foreach (QString param_name, parameters)
    {
        // Add a row
        // Row index to add row to
        const int rowNum = mpParametersTable->rowCount();
        // Add "blank" row
        mpParametersTable->insertRow(rowNum);
        // Fill blank row with values corresponding to this parameter
        // Set parameter name
        QLabel *paramNameWidget = new QLabel(param_name);
        mpParametersTable->setCellWidget(rowNum,paramColPos, paramNameWidget);
        // #iters spinbox
        QSpinBox *pIterationsSpinBox = new QSpinBox;
        pIterationsSpinBox->setRange(2,99);
        pIterationsSpinBox->setValue(3);
        pIterationsSpinBox->setAlignment(Qt::AlignRight);
        mpParametersTable->setCellWidget(rowNum,nItersColPos,pIterationsSpinBox);
        // Percentage spinbox
        QDoubleSpinBox *pPercentageBox = new QDoubleSpinBox;
        pPercentageBox->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        pPercentageBox->setValue(5);
        pPercentageBox->setSuffix("%");
        pPercentageBox->setPrefix("±");
        mpParametersTable->setCellWidget(rowNum,pertPercColPos,pPercentageBox);
        // Set checkbox
        QCheckBox *includeCheckBox = new QCheckBox;
        includeCheckBox->setChecked(false);
        mpParametersTable->setCellWidget(rowNum,cboxColPos,includeCheckBox);
    }
    // Set table settings
    // Resize columns to contents
    mpParametersTable->resizeColumnsToContents();

    QFormLayout *mainLayout = new QFormLayout;
    // Parameters table/list
    mainLayout->addRow(mpParametersTable);
    // Description
    mainLayout->addRow(mpBriefDescriptionLabel);
    setLayout(mainLayout);

}

QTableWidget *ParametersExtendedTab::getParametersTable() const
{
    return mpParametersTable;
}
