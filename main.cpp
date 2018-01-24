#include "omsens.h"
#include <EmpSensAnalysisDialog.h>
#include <MultiParamSweepDialog.h>
#include <CURVISensAnalysisDialog.h>

#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QStandardItem>
#include <QStandardItemModel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // OMSens w;
    // w.show();
    // Comment the "w.show()" and uncomment the following to test separately:
    //EmpSensAnalysisDialog *sensanaldialog = new EmpSensAnalysisDialog;
    //sensanaldialog->show();
    // CURVISensAnalysisDialog *curviDialog = new CURVISensAnalysisDialog;
    // curviDialog->show();
    MultiParamSweepDialog *mpsDialog = new MultiParamSweepDialog;
    mpsDialog->show();

    return a.exec();
}
