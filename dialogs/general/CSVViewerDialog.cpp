/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-2026, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF AGPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.8.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES
 * RECIPIENT'S ACCEPTANCE OF THE OSMC PUBLIC LICENSE OR THE GNU AGPL
 * VERSION 3, ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the OSMC (Open Source Modelica Consortium)
 * Public License (OSMC-PL) are obtained from OSMC, either from the above
 * address, from the URLs:
 * http://www.openmodelica.org or
 * https://github.com/OpenModelica/ or
 * http://www.ida.liu.se/projects/OpenModelica,
 * and in the OpenModelica distribution.
 *
 * GNU AGPL version 3 is obtained from:
 * https://www.gnu.org/licenses/licenses.html#GPL
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */

#include "CSVViewerDialog.h"

#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QGuiApplication>
#include <QDir>
#include "../../TableItemDelegate.h"

CSVViewerDialog::CSVViewerDialog(QString filePath, QWidget *parent) : QDialog(parent)
{
    QStandardItemModel *csvModel = standardItemModelFromFilePath(filePath);
    if (csvModel) {
      initializeTableWithStandardItemModel(csvModel);
      configureLayout();
    }
}

QStandardItemModel * CSVViewerDialog::standardItemModelFromFilePath(QString filePath)
{
    // Open file
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
      QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                               tr("Cannot open %1 for reading").arg(QDir::toNativeSeparators(filePath)));
      return nullptr;
    }
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
        // Convert to double every number so the notation is consistent (the column sort is buggy otherwise)

        for (int i = 0; i < cells.length(); i++ ) {
            QString itemStr = cells[i];
            bool ok;
            double d;
            d = itemStr.toDouble(&ok); // ok == true, d == 12.3456
            QStandardItem *stdItem = new QStandardItem(itemStr);
            // Assign a numeric QVariant if it's numeric
            if(ok){
                // If it's a valid double
                stdItem->setData(QVariant(d),Qt::DisplayRole);
            }
            standardItemsList.append(stdItem);
        }
        csvModel->insertRow(csvModel->rowCount(), standardItemsList);
    }
    // Close file
    file.close();

    return csvModel;
}

void CSVViewerDialog::initializeTableWithStandardItemModel(QStandardItemModel *csvModel)
{
    mpResultsTable = new QTableView(this);
    mpResultsTable->setModel(csvModel);
    // Resize columns to contents
    mpResultsTable->resizeColumnsToContents();
    mpResultsTable->setSortingEnabled(true);
    // Set item delegate to format doubles in specified precision
    TableItemDelegate *decDelegate = new TableItemDelegate(this);
    mpResultsTable->setItemDelegate(decDelegate);
    // Set table as readonly
    mpResultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void CSVViewerDialog::configureLayout()
{
    // New layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    // Assign table view to layout
    mainLayout->addWidget(mpResultsTable);
    // Set Dialog layout
    setLayout(mainLayout);
}

