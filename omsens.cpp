#include "omsens.h"
#include "ui_omsens.h"

#include <EmpSensAnalysisDialog.h>

OMSens::OMSens(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OMSens)
{
    ui->setupUi(this);
}

OMSens::~OMSens()
{
    delete ui;
}

void OMSens::on_actionEmpirical_Indices_triggered()
{
    EmpSensAnalysisDialog *sensanaldialog = new EmpSensAnalysisDialog;
    sensanaldialog->exec();
}
