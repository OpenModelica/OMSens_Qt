#include "omsens.h"
#include <EmpSensAnalysisDialog.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //OMSens w;
    //w.show();
    EmpSensAnalysisDialog *sensanaldialog = new EmpSensAnalysisDialog;
    sensanaldialog->show();

    return a.exec();
}
