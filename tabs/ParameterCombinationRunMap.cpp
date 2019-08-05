#include "tabs/ParameterCombinationRunMap.h"
#include <QVBoxLayout>
#include <QLabel>
#include "helpers/CSVReader.h"

ParameterCombinationRunMap::ParameterCombinationRunMap(QString mOMSensResultsPath, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    CSVReader *r = new CSVReader();
    QVector<QString> parameters = r->getColumnsNames(mOMSensResultsPath + "/" + "results/" + "parameters_run.csv");
    QVector<QVector<double>> rows = r->getNumericData(mOMSensResultsPath + "/" + "results/" + "parameters_run.csv");

    // Parameters table/list
    QTableWidget *table = new QTableWidget(0, parameters.size());
    const QList<QString> headers(parameters.toList());
    table->setHorizontalHeaderLabels(headers);

    // Declare the QPair outside the foreach because the commas are ambigous for Qt's macro
    for (int i=0; i<rows.size(); i++)
    {
        table->insertRow(table->rowCount());
        for (int j=0; j<rows[i].size(); j++)
        {
            QString new_item = QString::number(rows[i][j]);
            table->setItem( i, j, new QTableWidgetItem(new_item));
        }
    }

    // SET Layout
    mainLayout->addWidget(table);

    setLayout(mainLayout);
}
