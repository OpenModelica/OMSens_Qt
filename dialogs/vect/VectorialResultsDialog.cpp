#include "VectorialResultsDialog.h"

#include <QJsonObject>
#include <QStandardItemModel>
#include <QFormLayout>


VectorialResultsDialog::VectorialResultsDialog(QJsonDocument vectorialResults, QWidget *pParent) : QDialog(pParent)
{
    // Initialize tabs
    mpOptimParamsTab = new OptimizationResultParametersTab(vectorialResults);
    // Initialize tabs container widget
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpOptimParamsTab, tr("Parameters"));

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mpTabWidget);
    setLayout(mainLayout);

    // Windows settings
    this->setMinimumHeight(600);
    this->setMinimumWidth(600);

    // OLD:
//    // Parse JSON
//    // Get the "main" object of the json document
//    QJsonObject vectorialResultsObject = vectorialResults.object();
//    // Get the <param name> to <param value> mapper
//    mXOptMap = vectorialResultsObject.value(QString("x_opt")).toObject();
//    // Get f(x)
//    mFx = vectorialResultsObject.value(QString("f(x)_opt")).toDouble();
//
//    // Get parameters names
//    QList<QString> param_names = mXOptMap.keys();
//    // Initialize x vector table
//    int nRows = param_names.length();
//    const QList<QString> columnNames( QList<QString>()
//                                     << "Parameter"
//                                     << "Optimum Value"
//                                       );
//    int numberOfColumns = columnNames.length();
//
//    QStandardItemModel *csvModel = new QStandardItemModel(this);
//    csvModel->setColumnCount(numberOfColumns);
//    csvModel->setHorizontalHeaderLabels(columnNames);
//
//    // Iterate parameters and their values
//    foreach (QString param, param_names)
//    {
//        // Get parameter optimum value
//
//        // Initialize row
//        QList<QStandardItem *> standardItemsList;
//        // Initialize param name cell
//        QStandardItem *nameItem = new QStandardItem(param);
//        // Initialize optimum value
//        double optimumValue = mXOptMap.value(param).toDouble();
//        QStandardItem *optimumItem = new QStandardItem;
//        optimumItem->setData(QVariant(optimumValue),Qt::DisplayRole);
//        // Add the cells to the list
//        standardItemsList << nameItem << optimumItem;
//        // Insert the row into the model
//        csvModel->insertRow(csvModel->rowCount(), standardItemsList);
//    }
//
//    // x label
//    mpXLabel = new QLabel("x:");
//    // x table
//    mpXTable = new QTableView;
//    mpXTable->setModel(csvModel);
//    // Resize columns to contents
//    mpXTable->resizeColumnsToContents();
//    mpXTable->setSortingEnabled(true);
//    // Set item delegate to format doubles in specified precision
//    TableItemDelegate *decDelegate = new TableItemDelegate(this);
//    mpXTable->setItemDelegate(decDelegate);
//    // Set table as readonly
//    mpXTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
//
//    // Initialize f(x)
//    mpFxLabel = new QLabel("f(x):");
//    mpFxValue = new QLabel;
//    mpFxValue->setNum(mFx);
//
//    // Set layout
//    QFormLayout *pMainLayout = new QFormLayout;
//    // f(x)
//    QHBoxLayout *pFxLayout = new QHBoxLayout;
//    pFxLayout->addWidget(mpFxLabel);
//    pFxLayout->addWidget(mpFxValue);
//    pFxLayout->addStretch();
//    pMainLayout->addRow(pFxLayout);
//    // x
//    pMainLayout->addRow(mpXLabel);
//    pMainLayout->addRow(mpXTable);
//
//    // Layout settings
//    setLayout(pMainLayout);
}
