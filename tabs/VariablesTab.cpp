#include "VariablesTab.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QHeaderView>
#include <QLabel>

// Constructors
VariablesTab::VariablesTab(QList<VariableToInclude> vars_to_include, QWidget *parent) : QWidget(parent)
{
    mpVariablesTable = new QTableWidget(0, 2);
    const QList<QString> tableHeaders( QList<QString>()
                                     << "Variable"
                                     << "analyze?"
                                     );
    mpVariablesTable->setHorizontalHeaderLabels(tableHeaders);

    foreach (VariableToInclude var_include, vars_to_include)
    {
        // Add a row
        // Row index to add row to
        const int rowNum = mpVariablesTable->rowCount();
        // Add "blank" row
        mpVariablesTable->insertRow(rowNum);
        // Fill blank row with values corresponding to this variable
        // Set variable name
        QLabel *varNameWidget = new QLabel(var_include.name);
        mpVariablesTable->setCellWidget(rowNum,varColPos, varNameWidget);
        // Set checkbox
        // Wrap the checkbox in a generic QWidget so we can set a layout to center it in the cell
        QCheckBox *includeCheckBox = new QCheckBox;
        includeCheckBox->setChecked(var_include.include);
        mpVariablesTable->setCellWidget(rowNum,cboxColPos,includeCheckBox);
    }
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mpVariablesTable);
    setLayout(mainLayout);
}

// Methods
QTableWidget *VariablesTab::getVariablesTable() const
{
    return mpVariablesTable;
}
