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
    // f(x_opt)
    m_f_x_opt = vectorialResultsObject.value(QString("f(x)_opt")).toDouble();
    // f(x0)
    m_f_x0 = vectorialResultsObject.value(QString("f(x0)")).toDouble();
    // stop time
    mStopTime = vectorialResultsObject.value(QString("stop_time")).toDouble();
    // variable
    mVariable = vectorialResultsObject.value(QString("variable")).toString();

    // Stop time
    mpStopTimeLabel = new QLabel("Stop time:");
    mpStopTimeValue = new QLabel(QString::number(mStopTime));
    //mpStopTimeValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);

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
    mpFxLabel = new QLabel("Variable:");
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
    // stoptime
    pMainLayout->addRow(mpStopTimeLabel,mpStopTimeValue);
    // f(x)
    pMainLayout->addRow(mpFxLabel);
    QHBoxLayout  *pTableLayout = new QHBoxLayout;
    pTableLayout->addStretch();
    pTableLayout->addWidget(mpFxTable);
    pTableLayout->addStretch();
    pMainLayout->addRow(pTableLayout);

    // Layout settings
    setLayout(pMainLayout);
}
