#include "OMSensDialog.h"
#include "model.h"

#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QStandardItem>
#include <QStandardItemModel>

Model modelExample()
{
  const QList<QString> inputVariables( QList<QString>()
                                   << "population"
                                   << "nr_resources"
                                   << "human_welfare_index");
  const QList<QString> parameters( QList<QString>()
                                   << "laborForceDistribution"
                                   << "capitalDistribution"
                                   << "totalCapital"
                                   << "alfa"
                                   << "techProgressModifier"
                                   << "population_last_year");
  const QList<QString> outputVariables( QList<QString>()
                                   << "secGNP"
                                   << "outVar2");
  const QList<QString> auxVariables( QList<QString>()
                                   << "laborForce"
                                   << "secTotalSalaries"
                                   << "secCapital"
                                   << "grossSecGNP");
  //Aux
  Model model(inputVariables, outputVariables, auxVariables, parameters);
  return model;
}



int main(int argc, char *argv[])
{
    // Initialize Qt Application
    QApplication a(argc, argv);
    // Model information for testing:
    Model model = modelExample();
    // Initialize OMSens Dialog
    OMSensDialog dialog(model);
    // Show OMSens Dialog
    dialog.show();
    // Run and end Qt Application
    return a.exec();
}
