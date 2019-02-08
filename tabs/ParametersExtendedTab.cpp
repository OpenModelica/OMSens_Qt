#include "ParametersExtendedTab.h"

#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QComboBox>

ParametersExtendedTab::ParametersExtendedTab(QList<PerturbationRow> pert_rows, QWidget *parent) : QWidget(parent)
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
    // Sort rows before adding them so the "row" property is consistent
    std::sort(pert_rows.begin(), pert_rows.end());
    foreach (PerturbationRow row, pert_rows)
    {
        // Add a row
        // Row index to add row to
        const int rowNum = mpParametersTable->rowCount();
        // Add "blank" row
        mpParametersTable->insertRow(rowNum);
        // Fill blank row with values corresponding to this parameter
        // Set parameter name (needs to be widget item or it isn't sorted correctly)
        QTableWidgetItem *nameWidgetItem = new QTableWidgetItem(row.name);
        mpParametersTable->setItem(rowNum, nameColPos, nameWidgetItem);
        // Set perturbation type
        QComboBox *pTypeComboBox = new QComboBox;
        pTypeComboBox->setProperty("row", (int) rowNum);
        pTypeComboBox->addItem("None",  QVariant(NoPerturbationId));
        pTypeComboBox->addItem("Sweep", QVariant(SweepPerturbationId));
        pTypeComboBox->addItem("Fixed", QVariant(FixedPerturbationId));
        QVariant pert_type_qvariant = QVariant(row.perturbation_type_id);
        int pert_type_index = pTypeComboBox->findData(pert_type_qvariant);
        pTypeComboBox->setCurrentIndex(pert_type_index);
        connect(pTypeComboBox, SIGNAL(currentIndexChanged(int)),this, SLOT(pertTypeChanged(int)));
        mpParametersTable->setCellWidget(rowNum,pertTypeColPos, pTypeComboBox);
        // #iters spinbox
        QSpinBox *pIterationsSpinBox = new QSpinBox;
        pIterationsSpinBox->setRange(2,99);
        pIterationsSpinBox->setValue(row.iterations);
        pIterationsSpinBox->setAlignment(Qt::AlignRight);
        mpParametersTable->setCellWidget(rowNum,nItersColPos,pIterationsSpinBox);
        // Percentage spinbox
        QDoubleSpinBox *pPercentageBox = new QDoubleSpinBox;
        pPercentageBox->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        pPercentageBox->setValue(row.percentage);
        pPercentageBox->setSuffix("%");
        pPercentageBox->setPrefix("±");
        mpParametersTable->setCellWidget(rowNum,pertRangeColPos,pPercentageBox);
        // Set fixed value
        QDoubleSpinBox *fixedValueSpinBox = new QDoubleSpinBox;
        fixedValueSpinBox->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        fixedValueSpinBox->setValue(row.fixed_value);
        fixedValueSpinBox->setDecimals(4);
        mpParametersTable->setCellWidget(rowNum,fixedValueColPos,fixedValueSpinBox);

        // Enable/disable cells for this row depending on perturbation type
        enableOrDisableCellsOnRow(rowNum);
    }
    // Set table settings
    // Resize columns to contents
    mpParametersTable->resizeColumnsToContents();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    // Parameters table/list
    mainLayout->addWidget(mpParametersTable);
    // Description
    mainLayout->addWidget(mpBriefDescriptionLabel);
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

void ParametersExtendedTab::enableAllCells(int rowNum)
{
    QDoubleSpinBox *pPertRangeSpinbox= qobject_cast<QDoubleSpinBox *>(mpParametersTable->cellWidget(rowNum,pertRangeColPos));
    pPertRangeSpinbox->setEnabled(true);
    QSpinBox *pIterationsSpinbox= qobject_cast<QSpinBox *>(mpParametersTable->cellWidget(rowNum,nItersColPos));
    pIterationsSpinbox->setEnabled(true);
    QDoubleSpinBox *pFixedValueSpinbox = qobject_cast<QDoubleSpinBox *>(mpParametersTable->cellWidget(rowNum,fixedValueColPos));
    pFixedValueSpinbox->setEnabled(true);
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
        enableAllCells(rowNum);
        // If no perturbation was selected for this param, disable all the other columns
        disableNumberOfItersCellInRow(rowNum);
        disablePertRangeCellInRow(rowNum);
        disableFixedValueCellInRow(rowNum);
    }
    else if (perturbationTypeInt == SweepPerturbationId)
    {
        enableAllCells(rowNum);
        // If this parameter is to be swept, disable the fixed value cell
        disableFixedValueCellInRow(rowNum);
    }
    else if (perturbationTypeInt == FixedPerturbationId)
    {
        enableAllCells(rowNum);
        // If this parameter is to be fixed to a value in all simulations, disable the sweep columns
        disableNumberOfItersCellInRow(rowNum);
        disablePertRangeCellInRow(rowNum);
    }
}

void ParametersExtendedTab::pertTypeChanged(int)
{
    // Get row number of triggered combobox
    int rowNum = sender()->property("row").toInt();
    // Update cells state in row
    enableOrDisableCellsOnRow(rowNum);

}

