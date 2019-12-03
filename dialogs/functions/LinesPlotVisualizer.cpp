#include "LinesPlotVisualizer.h"
#include <QProcess>
#include <QProgressBar>
#include <QProgressDialog>
#include <QDateTime>
#include <QVBoxLayout>
#include <QImageReader>
#include <QVector>
#include <QComboBox>
#include <QMessageBox>
#include <string>
#include "dialogs/general/ImageViewerDialog.h"
#include "helpers/CSVReader.h"

LinesPlotVisualizer::LinesPlotVisualizer(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *pParent) : QDialog(pParent)
{
    executablePath = mPythonBinPath;
    librariesPath  = mOMSensPath;
    resultsPath    = mOMSensResultsPath;

    // Dialog settings
    setMinimumWidth(410);
    setWindowTitle("Histogram Creator");

    //CSVReader *csv_reader = new CSVReader();
    // TODO: for reuse in different contexts (apart from multiparameter sweep), these 3 files must be generated!
    //QVector<QString> parameters = csv_reader->getColumnsNames(mOMSensResultsPath + "/" + "results/" + "parameters_run.csv");
    //QVector<QString> variables = csv_reader->getColumnsNames(mOMSensResultsPath + "/" + "results/" + "variables.csv");
    //QVector<double> time_values = csv_reader->getColumnValues(mOMSensResultsPath + "/" + "results/runs/std_run.csv", "time");


    // Layout
    QVBoxLayout *pMainLayout = new QVBoxLayout;


    QLabel *options_variables_label = new QLabel("Variables (init vs. end): ");
    QHBoxLayout *row1 = new QHBoxLayout;
    row1->addWidget(options_variables_label);

    QDialogButtonBox *mpButtonBoxParameters = new QDialogButtonBox;
    mpButtonBoxParameters->addButton("Show", QDialogButtonBox::AcceptRole);
//    connect(mpButtonBoxParameters, &QDialogButtonBox::accepted, this, &HistogramCreator::showHistogramParameter);
    row1->addWidget(mpButtonBoxParameters);

    // Layout settings
    pMainLayout->addItem(row1);
    setLayout(pMainLayout);
}
