#include "omsens.h"
#include "ui_omsens.h"

#include <EmpSensAnalysisDialog.h>
#include <CURVISensAnalysisDialog.h>

OMSens::OMSens(QVector<QString> modelVars,QWidget *pParent) :
    QMainWindow(parent),
    ui(new Ui::OMSens), modelVars(modelVars)
{
    ui->setupUi(this);
}

OMSens::~OMSens()
{
    delete ui;
}

void OMSens::on_actionEmpirical_Indices_triggered()
{
    EmpSensAnalysisDialog *empiricalDialog = new EmpSensAnalysisDialog(modelVars);
    empiricalDialog->exec();
}

void OMSens::on_actionCURVI_Sens_triggered()
{
    CURVISensAnalysisDialog *curviDialog = new CURVISensAnalysisDialog;
    curviDialog->exec();
}
