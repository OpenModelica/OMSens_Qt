#include "ParametersExtendedTab.h"

#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QComboBox>


ParametersExtendedTab::ParametersExtendedTab(QList<QString> parameters, QWidget *parent) : QWidget(parent)
{
    // Initialize label with brief description of the sweep
    mpBriefDescriptionLabel = new QLabel("The total #iterations will be the product of the #iterations of all the parameters.");
    //Initialize table header
    mpParametersTable = new QTableWidget(0, 5);
    const QList<QString> tableHeaders( QList<QString>()
                                     << "Parameter"
                                     << "Perturbation Type"
                                     << "#iter"
                                     << "Sweep Range"
                                     << "Fixed value"
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
        // Set perturbation type
        QComboBox *pTypeComboBox = new QComboBox;
        pTypeComboBox->addItem("None",  QVariant(NoPerturbationId));
        pTypeComboBox->addItem("Sweep", QVariant(SweepPerturbationId));
        pTypeComboBox->addItem("Fixed", QVariant(FixedPerturbationId));
        mpParametersTable->setCellWidget(rowNum,pertTypeColPos, pTypeComboBox);
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
        mpParametersTable->setCellWidget(rowNum,pertRangeColPos,pPercentageBox);
        // Set fixed value
        QDoubleSpinBox *fixedValueSpinBox = new QDoubleSpinBox;
        pPercentageBox->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        pPercentageBox->setValue(42);
        mpParametersTable->setCellWidget(rowNum,fixedValueColPos,fixedValueSpinBox);

        // Enable/disable cells for this row depending on perturbation type
        enableOrDisableCellsOnRow(rowNum);
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

void ParametersExtendedTab::disableFixedValueCellInRow(int rowNum)
{
    QDoubleSpinBox *pFixedValueSpinbox = qobject_cast<QDoubleSpinBox *>(mpParametersTable->cellWidget(rowNum,fixedValueColPos));
    pFixedValueSpinbox->setEnabled(false);
}

void ParametersExtendedTab::disablePertRangeCellInRow(int rowNum)
{
    QDoubleSpinBox *pPertRangeSpinbox= qobject_cast<QDoubleSpinBox *>(mpParametersTable->cellWidget(rowNum,pertRangeColPos));
    pPertRangeSpinbox->setEnabled(false);
}

void ParametersExtendedTab::disableNumberOfItersCellInRow(int rowNum)
{
    QSpinBox *pIterationsSpinbox= qobject_cast<QSpinBox *>(mpParametersTable->cellWidget(rowNum,nItersColPos));
    pIterationsSpinbox->setEnabled(false);
}

void ParametersExtendedTab::enableOrDisableCellsOnRow(int rowNum)
{
    // Depending on the perturbation type, some cells will be enabled and others disabled
    QComboBox *rowComboBox = qobject_cast<QComboBox *>(mpParametersTable->cellWidget(rowNum,pertTypeColPos));
    QVariant perturbationTypeQVariant = rowComboBox->itemData(rowComboBox->currentIndex());
    int perturbationTypeInt = perturbationTypeQVariant.toInt();
    // I have to use an if because the ints defining the perturbation types are not constant for switches and
    //   enums are tedious to use in qvariants
    if (perturbationTypeInt == NoPerturbationId)
    {
        // If no perturbation was selected for this param, disable all the other columns
        disableNumberOfItersCellInRow(rowNum);
        disablePertRangeCellInRow(rowNum);
        disableFixedValueCellInRow(rowNum);
    }
    else if (perturbationTypeInt == SweepPerturbationId)
    {
        // If this parameter is to be swept, disable the fixed value cell
        disableNumberOfItersCellInRow(rowNum);
        disablePertRangeCellInRow(rowNum);
    }
    else if (perturbationTypeInt == FixedPerturbationId)
    {
        // If this parameter is to be fixed to a value in all simulations, disable the sweep columns
        disableFixedValueCellInRow(rowNum);
    }
}
