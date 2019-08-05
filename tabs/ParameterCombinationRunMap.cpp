#include "tabs/ParameterCombinationRunMap.h"
#include <QVBoxLayout>
#include <QLabel>
#include "helpers/CSVReader.h"

ParameterCombinationRunMap::ParameterCombinationRunMap(QString mOMSensResultsPath, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    CSVReader *r = new CSVReader();
    QVector<QString> parameters = r->getColumnsNames(mOMSensResultsPath + "/" + "results/" + "parameters_run.csv");
    QVector<QString> variables = r->getColumnsNames(mOMSensResultsPath + "/" + "results/" + "variables.csv");

    // Parameters table/list
//    QLabel *label1 = new QLabel(mOMSensResultsPath);
    QLabel *label1 = new QLabel(parameters.at(0));

    mainLayout->addWidget(label1, 0, Qt::AlignLeft);


    // model_info.json
    // parameters, aux_variables, input_variables


    setLayout(mainLayout);
}
