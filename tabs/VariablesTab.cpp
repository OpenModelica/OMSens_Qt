#include "VariablesTab.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QHeaderView>
#include <QLabel>

VariablesTab::VariablesTab(QList<QString> variables, QWidget *parent) : QWidget(parent)
{
    //Initialize table header
    mpVariablesTable = new QTableWidget(0, 2);
    const QList<QString> tableHeaders( QList<QString>()
                                     << "Variable"
                                     << "analyze?"
                                     );
    mpVariablesTable->setHorizontalHeaderLabels(tableHeaders);

    foreach (QString variable, variables)
    {
        // Add a rowº
        // Row index to add row to
        const int rowNum = mpVariablesTable->rowCount();
        // Add "blank" row
        mpVariablesTable->insertRow(rowNum);
        // Fill blank row with values corresponding to this variable
        // Set variable name
        QLabel *varNameWidget = new QLabel(variable);
        mpVariablesTable->setCellWidget(rowNum,varColPos, varNameWidget);
        // Set checkbox
        // Wrap the checkbox in a generic QWidget so we can set a layout to center it in the cell
        QCheckBox *includeCheckBox = new QCheckBox;
        includeCheckBox->setChecked(true);
        mpVariablesTable->setCellWidget(rowNum,cboxColPos,includeCheckBox);
    }
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mpVariablesTable);
    setLayout(mainLayout);
}

QTableWidget *VariablesTab::getVariablesTable() const
{
    return mpVariablesTable;
}
