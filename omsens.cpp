#include "omsens.h"
#include "ui_omsens.h"
#include "model.h"

#include <EmpSensAnalysisDialog.h>
#include <CURVISensAnalysisDialog.h>
#include <MultiParamSweepDialog.h>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QStandardItemModel>

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
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("Open Python Script"), "", tr("Python script(*.py)"));
    QString pythonBinPath = "/home/adanos/anaconda3/bin/python";
    QString command = QString(pythonBinPath) + " " + fileName;
    QFileInfo fileNameFileInfo = QFileInfo(fileName);
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
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("Open Sens Analysis Results"), "", tr("Comma Separated Values file(*.csv)"));
    // Open file
    QFile file(fileName);
    file.open(QFile::ReadOnly | QFile::Text);
    // Create a thread to retrieve data from a file
    QTextStream in(&file);
    // Read first row into column names
    QString columnNamesLine = in.readLine();
    QList<QString> columnNames = columnNamesLine.split(",");
    int numberOfColumns = columnNames.length();
    // Create table from columns data
    QStandardItemModel *csvModel;
    csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(numberOfColumns);
    // Read the rest of the lines. Each one will correspond to a parameter result
    while (!in.atEnd())
    {
        QString line = in.readLine();
        // Adding to the model in line with the elements
        QList<QStandardItem *> standardItemsList;
        // consider that the line separated by semicolons into columns
        QList<QString> cells = line.split(";");
        for (int i = 0; i < cells.length(); i++ ) {
            QString item = cells[i];
            standardItemsList.append(new QStandardItem(item));
        }
        csvModel->insertRow(csvModel->rowCount(), standardItemsList);
    }
    // Close file
    file.close();
    // Assign model to window
// DESDE ACA FALTA
//    QWindow csvWindow;
//    ui->tableView->setModel(csvModel);
// HASTA ACA FALTA
}
