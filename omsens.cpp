#include "omsens.h"
#include "ui_omsens.h"
#include "model.h"

#include <EmpSensAnalysisDialog.h>
#include <CURVISensAnalysisDialog.h>
#include <MultiParamSweepDialog.h>
#include <SensitivityAnalysisResultDialog.h>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>

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

void OMSens::on_actionRun_Script_triggered()
{
    QString filePath;
    filePath = QFileDialog::getOpenFileName(this,tr("Open Python Script"), "", tr("Python script(*.py)"));
    QString pythonBinPath = "/home/adanos/anaconda3/bin/python";
    QString command = QString(pythonBinPath) + " " + filePath;
    QFileInfo fileNameFileInfo = QFileInfo(filePath);
    QDir      fileDir          = fileNameFileInfo.canonicalPath();
    QString fileDirPath        = fileDir.canonicalPath();
    bool currentDirChangeSuccessful = QDir::setCurrent(fileDirPath);
    if (currentDirChangeSuccessful)
    {
        system(qPrintable(command));
    }
}

void OMSens::on_actionOpen_Sens_Analysis_Result_triggered()
{

    // Ask for file path using dialog
    QString filePath = QFileDialog::getOpenFileName(this,tr("Open Sens Analysis Results"), "", tr("Comma Separated Values file(*.csv)"));
    // Check if the user selected a file or if they clicked cancel
    if (!filePath.isNull()){
        // Initialize Results dialog
        SensitivityAnalysisResultDialog *mpSensResult = new SensitivityAnalysisResultDialog(filePath);
        mpSensResult->exec();
    }
}

void OMSens::on_actionRun_Curvi_Sens_Script_triggered()
{
    QString testFilePath = QFileDialog::getOpenFileName(this,tr("Open Curvi Sens Script"), "", tr("Curvi Sens script(*.txt)"));
    QString curviSensOutputPath = QString("/tmp/curviOutput_omedit.csv");
    QString curviSensBinPath = "/home/adanos/Documents/repos/tesis-work/modelica_scripts/fortran/curvi";
    QString command = QString(curviSensBinPath) + " " + testFilePath + " " + curviSensOutputPath;
    QFileInfo curviSensFileInfo = QFileInfo(curviSensBinPath);
    QDir      fileDir          = curviSensFileInfo.canonicalPath();
    QString fileDirPath        = fileDir.canonicalPath();
    bool currentDirChangeSuccessful = QDir::setCurrent(fileDirPath);
    if (currentDirChangeSuccessful)
    {
        system(qPrintable(command));
    }
}
