#include "SensitivityAnalysisResultDialog.h"

#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QTableView>
#include <QVBoxLayout>

SensitivityAnalysisResultDialog::SensitivityAnalysisResultDialog(QString filePath, QWidget *parent) : QDialog(parent)
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
    // Assign csv model to table view
    mpResultsTable = new QTableView;
    mpResultsTable->setModel(csvModel);
    // Assign table view to layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mpResultsTable);
    setLayout(mainLayout);
    // Close file
    file.close();
}
