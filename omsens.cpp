#include "omsens.h"
#include "ui_omsens.h"

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

void OMSens::on_actionRel_Sens_triggered()
{

}
