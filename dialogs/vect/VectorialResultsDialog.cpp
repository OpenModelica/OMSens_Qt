#include "VectorialResultsDialog.h"

#include <QJsonObject>
#include <QStandardItemModel>
#include <QFormLayout>

#include "OMSens/TableItemDelegate.h"

VectorialResultsDialog::VectorialResultsDialog(QJsonDocument vectorialResults, QWidget *pParent) : QDialog(pParent)
{
    // Parse JSON
    // Get the "main" object of the json document
    QJsonObject vectorialResultsObject = vectorialResults.object();
    // Get the <param name> to <param value> mapper
    mXOptMap = vectorialResultsObject.value(QString("x_opt")).toObject();
    // Get f(x)
    mFx = vectorialResultsObject.value(QString("f(x)_opt")).toDouble();

    // Get parameters names
    QList<QString> param_names = mXOptMap.keys();
    // Initialize x vector table
    int nRows = param_names.length();
    const QList<QString> columnNames( QList<QString>()
                                     << "Parameter"
                                     << "Optimum Value"
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
        // Initialize optimum value
        double optimumValue = mXOptMap.value(param).toDouble();
        QStandardItem *optimumItem = new QStandardItem;
        optimumItem->setData(QVariant(optimumValue),Qt::DisplayRole);
        // Add the cells to the list
        standardItemsList << nameItem << optimumItem;
        // Insert the row into the model
        csvModel->insertRow(csvModel->rowCount(), standardItemsList);
    }

    // x label
    mpXLabel = new QLabel("x:",this);
    // x table
    mpXTable = new QTableView(this);
    mpXTable->setModel(csvModel);
    // Resize columns to contents
    mpXTable->resizeColumnsToContents();
    mpXTable->setSortingEnabled(true);
    // Set item delegate to format doubles in specified precision
    TableItemDelegate *decDelegate = new TableItemDelegate(this);
    mpXTable->setItemDelegate(decDelegate);
    // Set table as readonly
    mpXTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Initialize f(x)
    mpFxLabel = new QLabel("f(x):",this);
    mpFxValue = new QLabel(this);
    mpFxValue->setNum(mFx);

    // Set layout
    QFormLayout *pMainLayout = new QFormLayout(this);
    // f(x)
    QHBoxLayout *pFxLayout = new QHBoxLayout(this);
    pFxLayout->addWidget(mpFxLabel);
    pFxLayout->addWidget(mpFxValue);
    pFxLayout->addStretch();
    pMainLayout->addRow(pFxLayout);
    // x
    pMainLayout->addRow(mpXLabel);
    pMainLayout->addRow(mpXTable);

    // Layout settings
    setLayout(pMainLayout);
}
