#include "SensitivityAnalysisResultDialog.h"

#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>

SensitivityAnalysisResultDialog::SensitivityAnalysisResultDialog(QString filePath, QWidget *parent) : QDialog(parent)
{
    QStandardItemModel *csvModel = standardItemModelFromFilePath(filePath);
    initializeTableWithStandardItemModel(csvModel);
    configureLayout();
}

QStandardItemModel * SensitivityAnalysisResultDialog::standardItemModelFromFilePath(QString filePath)
{
    // Open file
    QFile file(filePath);
    file.open(QFile::ReadOnly | QFile::Text);
    // Create a thread to retrieve data from a file
    QTextStream in(&file);
    // Read first row into column names
    QString columnNamesLine = in.readLine();
    QList<QString> columnNames = columnNamesLine.split(",");
    int numberOfColumns = columnNames.length();
    // Create table from columns data
    QStandardItemModel *csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(numberOfColumns);
        csvModel->setHorizontalHeaderLabels(columnNames);
    // Read the rest of the lines. Each one will correspond to a parameter result
    while (!in.atEnd())
    {
        QString line = in.readLine();
        // Adding to the model in line with the elements
        QList<QStandardItem *> standardItemsList;
        // consider that the line separated by semicolons into columns
        QList<QString> cells = line.split(",");
        for (int i = 0; i < cells.length(); i++ ) {
            QString item = cells[i];
            standardItemsList.append(new QStandardItem(item));
        }
        csvModel->insertRow(csvModel->rowCount(), standardItemsList);
    }
    // Close file
    file.close();

    return csvModel;
}

void SensitivityAnalysisResultDialog::initializeTableWithStandardItemModel(QStandardItemModel *csvModel)
{
    mpResultsTable = new QTableView;
    mpResultsTable->setModel(csvModel);
    // Resize columns to contents
    mpResultsTable->resizeColumnsToContents();
    mpResultsTable->setSortingEnabled(true);
}

void SensitivityAnalysisResultDialog::configureLayout()
{
    // New layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    // Assign table view to layout
    mainLayout->addWidget(mpResultsTable);
    // Set Dialog layout
    setLayout(mainLayout);
}

