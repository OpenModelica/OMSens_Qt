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

#include "OptimizationResultOtherTab.h"

#include <QStandardItemModel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFormLayout>
#include <QHeaderView>

#include "../../TableItemDelegate.h"

OptimizationResultOtherTab::OptimizationResultOtherTab(QJsonDocument vectorialResults, QWidget *pParent) : QTabWidget(pParent)
{
    // Parse JSON
    // Get the "main" object of the json document
    QJsonObject vectorialResultsObject = vectorialResults.object();
    // Get the results
    m_f_x_opt = vectorialResultsObject.value(QString("f(x)_opt")).toDouble();
    m_f_x0 = vectorialResultsObject.value(QString("f(x0)")).toDouble();
    mVariable = vectorialResultsObject.value(QString("variable")).toString();


    // Initialize f(x) table
    const QList<QString> columnNames( QList<QString>()
                                     << "Variable"
                                     << "Default"
                                     << "Optimum"
                                     << "Change (%)"
                                       );
    int numberOfColumns = columnNames.length();

    QStandardItemModel *csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(numberOfColumns);
    csvModel->setHorizontalHeaderLabels(columnNames);

    // Initialize row
    QList<QStandardItem *> standardItemsList;
    // Initialize variable name cell
    QStandardItem *nameItem = new QStandardItem(mVariable);
    // Initialize default value
    QStandardItem *defaultItem = new QStandardItem;
    defaultItem->setData(QVariant(m_f_x0),Qt::DisplayRole);
    // Initialize optimum value
    QStandardItem *optimumItem = new QStandardItem;
    optimumItem->setData(QVariant(m_f_x_opt),Qt::DisplayRole);
    // Check if the optimum value ended up being 0
    QVariant changeVariant;
    if (m_f_x0 != 0)
    {
        // If we can divide, define change as follows
        double change = ((m_f_x_opt/m_f_x0)-1)*100;
        changeVariant = QVariant(change);
    }
    else
    {
        // If we can't divide, define as follows
        QString change = "#ERROR";
        changeVariant = QVariant(change);
    }
    // Initialize change
    QStandardItem *changeItem = new QStandardItem;
    changeItem->setData(changeVariant,Qt::DisplayRole);
    // Add the cells to the list
    standardItemsList << nameItem << defaultItem << optimumItem << changeItem;
    // Insert the row into the model
    csvModel->insertRow(csvModel->rowCount(), standardItemsList);

    // f(x) table
    mpFxTable = new QTableView;
    mpFxTable->setModel(csvModel);
    // Disable row label
    mpFxTable->verticalHeader()->setVisible(false);
    // Disable scrollbars
    mpFxTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mpFxTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Set item delegate to format doubles in specified precision
    TableItemDelegate *decDelegate = new TableItemDelegate(this);
    mpFxTable->setItemDelegate(decDelegate);
    // Set table as readonly
    mpFxTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Resize columns to contents
    mpFxTable->resizeColumnsToContents();
    // Set fixed width and height for whole table
    int width  = mpFxTable->horizontalHeader()->length();
    int height = mpFxTable->verticalHeader()->length()   + mpFxTable->horizontalHeader()->height();
    mpFxTable->setFixedSize(width, height);
    // Disable column resize
    mpFxTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // Set layout
    QFormLayout  *pMainLayout = new QFormLayout;
    // f(x)
    QHBoxLayout  *pTableLayout = new QHBoxLayout;
    pTableLayout->addStretch();
    pTableLayout->addWidget(mpFxTable);
    pTableLayout->addStretch();
    pMainLayout->addRow(pTableLayout);


    // Layout settings
    setLayout(pMainLayout);
}
