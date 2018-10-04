#include "VariablesTab.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QHeaderView>
#include <QLabel>

VariablesTab::VariablesTab(QList<QString> variables, QWidget *parent) : QWidget(parent)
{
    //Initialize table header
    mpVariablesTable = new QTableWidget(0, 2, this);
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
        QLabel *varNameWidget = new QLabel(variable, this);
        mpVariablesTable->setCellWidget(rowNum,varColPos, varNameWidget);
        // Set checkbox
        // Wrap the checkbox in a generic QWidget so we can set a layout to center it in the cell
        QCheckBox *includeCheckBox = new QCheckBox(this);
        includeCheckBox->setChecked(true);
        mpVariablesTable->setCellWidget(rowNum,cboxColPos,includeCheckBox);


        // The following centers the checkbox but we can't get the checkbox when iterating the table
//        QWidget *cell_widget = new QWidget(this);
//        QHBoxLayout *lay_out = new QHBoxLayout(this);
//        lay_out->addWidget(includeCheckBox);
//        lay_out->setAlignment(Qt::AlignCenter);
//        lay_out->setContentsMargins(0,0,0,0);
//        cell_widget->setLayout(lay_out);
//        mpVariablesTable->setCellWidget(rowNum,cboxColPos,cell_widget);
    }
    // Set table settings
    // Hide grid
//    variablesTable->setShowGrid(false);
    // Resize columns to contents
    mpVariablesTable->resizeColumnsToContents();
    // Edit scrollbars
//    variablesTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    variablesTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
//    variablesTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Settings with QHeaderView:
//    QHeaderView *headerView = variablesTable->verticalHeader();
    // Hide line counter
//    headerView->setVisible(false);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(mpVariablesTable);
    //mainLayout->addStretch(1);
    setLayout(mainLayout);
}

QTableWidget *VariablesTab::getVariablesTable() const
{
    return mpVariablesTable;
}
