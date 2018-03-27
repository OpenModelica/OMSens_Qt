#include "omsens.h"
#include <IndivParamSensAnalysisDialog.h>
#include <MultiParamSweepDialog.h>
#include <VectorialParamSensAnalysisDialog.h>

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
    QApplication a(argc, argv);
    // Model information for testing:
    Model model = modelExample();
     OMSens w(model);
     w.show();
    // Comment the "w.show()" and uncomment the following to test separately:
    //EmpSensAnalysisDialog *sensanaldialog = new EmpSensAnalysisDialog(model);
    //sensanaldialog->show();
    // CURVISensAnalysisDialog *curviDialog = new CURVISensAnalysisDialog(model);
    // curviDialog->show();
    // MultiParamSweepDialog *mpsDialog = new MultiParamSweepDialog(model);
    // mpsDialog->show();

    //int aExec= a.exec();
    //delete pModel;
    return a.exec();
}
