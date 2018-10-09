#include "OptimizationResultParametersTab.h"

#include <QStandardItemModel>
#include "../../TableItemDelegate.h"

#include <QHBoxLayout>

OptimizationResultParametersTab::OptimizationResultParametersTab(QJsonDocument vectorialResults, QWidget *pParent) : QTabWidget(pParent)
{
    // Parse JSON
    // Get the "main" object of the json document
    QJsonObject vectorialResultsObject = vectorialResults.object();
    // Get the optimal parameters
    m_x_opt = vectorialResultsObject.value(QString("x_opt")).toObject();
    // Get standard parameters
    m_x0 = vectorialResultsObject.value(QString("x0")).toObject();

    // Get parameters names
    QList<QString> param_names = m_x_opt.keys();
    // Initialize table
    const QList<QString> columnNames( QList<QString>()
                                     << "Parameter"
                                     << "Default"
                                     << "Optimum"
                                     << "Change (%)"
                                       );
    int numberOfColumns = columnNames.length();

    QStandardItemModel *csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(numberOfColumns);
    csvModel->setHorizontalHeaderLabels(columnNames);

    // Iterate parameters and their values
    foreach (QString param, param_names)
    {
        // Get parameter optimum value

        // Initialize row
        QList<QStandardItem *> standardItemsList;
        // Initialize param name cell
        QStandardItem *nameItem = new QStandardItem(param);
        // Initialize default value
        double defaultValue = m_x0.value(param).toDouble();
        QStandardItem *defaultItem = new QStandardItem;
        defaultItem->setData(QVariant(defaultValue),Qt::DisplayRole);
        // Initialize optimum value
        double optimumValue = m_x_opt.value(param).toDouble();
        QStandardItem *optimumItem = new QStandardItem;
        optimumItem->setData(QVariant(optimumValue),Qt::DisplayRole);
        // Check if the optimum value ended up being 0
        QVariant changeVariant;
        if (defaultValue != 0)
        {
            // If we can divide, define change as follows
            double change = ((optimumValue/defaultValue)-1)*100;
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
    }

    // x table
    mpXTable = new QTableView;
    mpXTable->setModel(csvModel);
    // Enable sorting
    mpXTable->setSortingEnabled(true);
    // Set item delegate to format doubles in specified precision
    TableItemDelegate *decDelegate = new TableItemDelegate(this);
    mpXTable->setItemDelegate(decDelegate);
    // Set table as readonly
    mpXTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Resize columns to contents
    mpXTable->resizeColumnsToContents();

    // Set layout
    QHBoxLayout *pMainLayout = new QHBoxLayout;
    pMainLayout->addWidget(mpXTable);

    // Layout settings
    setLayout(pMainLayout);
}
