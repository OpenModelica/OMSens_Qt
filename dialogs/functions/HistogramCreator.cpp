#include "HistogramCreator.h"
#include <QProcess>
#include <QProgressBar>
#include <QProgressDialog>
#include <QDateTime>
#include <QVBoxLayout>
#include <QImageReader>
#include <QVector>
#include <QComboBox>
#include <string>
#include "../dialogs/general/ImageViewerDialog.h"
#include "../helpers/CSVReader.h"

using namespace std;

HistogramCreator::HistogramCreator(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *pParent) : QDialog(pParent)
{
    executablePath = mPythonBinPath;
    librariesPath  = mOMSensPath;
    resultsPath    = mOMSensResultsPath;

    // Dialog settings
    setMinimumWidth(410);
    setWindowTitle("Histogram Creator");

    // TODO: dar opciones de parametros sobre los cuales hacer el histograma (van a depender de cada experimento)
    //       set parameters for later using in makePNG function.
    // Interface for selecting desired histogram parameters
    // result filename path (where to go and fetch the PNG)
    // input csv file
    // t_{obs}: time of simulation for which the histogram will be made
    // var    : variable for which the histogram will me made (for it's value on time t=t_{obs})
    CSVReader *csv_reader = new CSVReader();

    // Obtener nombres de las VARIABLES del modelo (TODO: Ir a buscar al archivo correpondiente)
    QVector<QString> columns = csv_reader->getColumnsNames(resultsPath + "/results/" + "runs/std_run.csv");

    // TODO: Obtener nombre de los PARAMETROS del modelo (TODO: ir a buscar al archivo correspondiente)


    // Layout
    QVBoxLayout *pMainLayout = new QVBoxLayout;

    // Options parameters
    QLabel *time_label = new QLabel("Time: ");
    options_time_box = new QComboBox;
    options_time_box->addItem("2");
    QHBoxLayout *row1 = new QHBoxLayout;
    row1->addWidget(time_label);
    row1->addWidget(options_time_box);
    pMainLayout->addItem(row1);

    QLabel *options_parameters_label = new QLabel("Variable: ");
    options_parameters_box = new QComboBox;
    for (QString columnName: columns) {
        options_parameters_box->addItem(columnName);
    }
    QHBoxLayout *row2 = new QHBoxLayout;
    row2->addWidget(options_parameters_label);
    row2->addWidget(options_parameters_box);
    pMainLayout->addItem(row2);

    // parameters buttons
    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("Show Plot", QDialogButtonBox::AcceptRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &HistogramCreator::showHistogram);
    pMainLayout->addWidget(mpButtonBox, 0, Qt::AlignLeft);

    // Layout settings
    setLayout(pMainLayout);
}

void HistogramCreator::showHistogram()
{
    // Generate filename of png to fetch/generate, using the input parameters entered by the user
//    QString fileNamePath = resultsPath + "/results/" + "plots/" + options_time_box->currentText()
//            + "_" + options_parameters_box->currentText() + ".png";
    QString fileNamePath = resultsPath + "/results/" + "plots/"
            + "h_"
            + QString::number(options_time_box->currentIndex())
            + "_" + QString::number(options_parameters_box->currentIndex())
            + ".png";

    // Check if PNG is available. If it is not, generate it
    QImageReader reader(fileNamePath);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        makePNG(fileNamePath);
    }
//    else{
    ImageViewerDialog *pImageViewer = new ImageViewerDialog(fileNamePath, this);
    pImageViewer->show();
//    }
}

int HistogramCreator::makePNG(QString png_filename_path)
{
    // Get parameters
    QString scriptPathBaseDir = librariesPath;
    QString scriptPath        = librariesPath + "callable_methods/plot_histogram.py";
    QString pythonBinPath     = executablePath;

    QString args = "--filename_path=" + png_filename_path
            + " " + "--parameter=" + options_parameters_box->currentText()
            + " " + "--time_value=" + options_time_box->currentText()
            + " " + "--runs_path=" + resultsPath + "/results/runs";

    // GENERATE COMMAND FROM SELECTED PARAMETERS


    // RUN PROCESS
    QString command = pythonBinPath + " " + scriptPath + " " + args;
    QProcess pythonScriptProcess;
    pythonScriptProcess.setWorkingDirectory(scriptPathBaseDir);

    // Initialize dialog showing progress
    QString progressDialogText = progressDialogTextForCurrentTime();
    QProgressDialog *dialog = new QProgressDialog(progressDialogText, "Cancel", 0, 0, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    connect(&pythonScriptProcess, SIGNAL(finished(int)), dialog, SLOT(close()));
    connect(dialog, SIGNAL(canceled()), &pythonScriptProcess, SLOT(kill()));

    // Start process
    pythonScriptProcess.start(command);
    // Show dialog with progress
    dialog->exec();
    // Wait for the process to finish in the case that we cancel the process and it doesn't have time to finish correctly
    pythonScriptProcess.waitForFinished(3000);
    // See if the process ended correctly
    QProcess::ExitStatus exitStatus = pythonScriptProcess.exitStatus();
    int exitCode = pythonScriptProcess.exitCode();
    bool processEndedCorrectly = (exitStatus == QProcess::NormalExit) && (exitCode == 0);
    return processEndedCorrectly;
}

QString HistogramCreator::progressDialogTextForCurrentTime()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString date = currentTime.toString("dd/MM/yyyy");
    QString h_m_s = currentTime.toString("H:m:s");
    QString scriptRunStartString = "(started on " + date + " at " + h_m_s + ")";
    QString progressDialogText = "Running python script... " + scriptRunStartString;
    return progressDialogText;
}
