#include "HistogramCreator.h"
#include <QProcess>
#include <QProgressBar>
#include <QProgressDialog>
#include <QDateTime>
#include <QVBoxLayout>
#include <QImageReader>
#include "../dialogs/general/ImageViewerDialog.h"
#include <string>

using namespace std;

HistogramCreator::HistogramCreator(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *pParent) : QDialog(pParent)
{
    executablePath = mPythonBinPath;
    librariesPath  = mOMSensPath;
    resultsPath    = mOMSensResultsPath;

    // Dialog settings
    setMinimumWidth(410);
    setWindowTitle("Histogram Creator");
    QVBoxLayout *pMainLayout = new QVBoxLayout;

    // TODO: dar opciones de parametros sobre los cuales hacer el histograma (van a depender de cada experimento)
    //       set parameters for later using in makePNG function.
    // Interface for selecting desired histogram parameters
    // result filename path (where to go and fetch the PNG)
    // input csv file
    // t_{obs}: time of simulation for which the histogram will be made
    // var    : variable for which the histogram will me made (for it's value on time t=t_{obs})

    // TODO: el nombre especifico del plot va a depender de los parametros especificos del histograma
    plotName = "plots/zzz.png";

    // parameters buttons
    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("Show Plot", QDialogButtonBox::AcceptRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &HistogramCreator::showHistogram);
    pMainLayout->addWidget(mpButtonBox, 0, Qt::AlignCenter);

    // Layout settings
    setLayout(pMainLayout);
}

void HistogramCreator::showHistogram()
{
    // Generate filename of png to fetch/generate, using the input parameters entered by the user
    QString fileNamePath = resultsPath + "/" + plotName;

    // Check if PNG is available. If it is not, generate it
    QImageReader reader(fileNamePath);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        makePNG(fileNamePath);
    }
    else{
        ImageViewerDialog *pImageViewer = new ImageViewerDialog(fileNamePath, this);
        pImageViewer->show();
    }
}

int HistogramCreator::makePNG(QString png_filename_path)
{
    // Get parameters
    QString scriptPathBaseDir = librariesPath;
    QString scriptPath        = librariesPath + "callable_methods/plot_histogram.py";
    QString pythonBinPath     = executablePath;

    QString args = "--filename_path=" + png_filename_path;

    // GENERATE COMMAND FROM SELECTED PARAMETERS


    // TODO: Append parameter to command
    QString command = pythonBinPath + " " + scriptPath + " " + args;

    // RUN PROCESS
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
