#include "omsens.h"
#include "ui_omsens.h"
#include "model.h"

#include <EmpSensAnalysisDialog.h>
#include <CURVISensAnalysisDialog.h>
#include <MultiParamSweepDialog.h>

OMSens::OMSens(Model model,QWidget *pParent) :
    QMainWindow(pParent),
    ui(new Ui::OMSens), model(model)
{
    ui->setupUi(this);
}

OMSens::~OMSens()
{
    delete ui;
}

void OMSens::on_actionEmpirical_Indices_triggered()
{
    EmpSensAnalysisDialog *empiricalDialog = new EmpSensAnalysisDialog(model);
    empiricalDialog->exec();
}

void OMSens::on_actionCURVI_Sens_triggered()
{
    CURVISensAnalysisDialog *curviDialog = new CURVISensAnalysisDialog(model);
    curviDialog->exec();
}

void OMSens::on_actionMultiparam_Sweep_triggered()
{
    MultiParamSweepDialog *mpsDialog = new MultiParamSweepDialog(model);
    mpsDialog->exec();

}
