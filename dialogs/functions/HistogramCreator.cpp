#include "HistogramCreator.h"
#include <QProcess>
#include <QProgressBar>
#include <QProgressDialog>
#include <QDateTime>
#include <QVBoxLayout>
#include <QImageReader>
#include "../dialogs/general/ImageViewerDialog.h"

HistogramCreator::HistogramCreator(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *pParent) : QDialog(pParent)
{
    executablePath = mPythonBinPath;
    librariesPath  = mOMSensPath;
    resultsPath    = mOMSensResultsPath;

    // Dialog settings
    setMinimumWidth(410);
    setWindowTitle("Histogram Creator");
    QVBoxLayout *pMainLayout = new QVBoxLayout;

    // Interface for selecting desired histogram parameters
    // result filename path (where to go and fetch the PNG)
    // input csv file
    // t_{obs}: time of simulation for which the histogram will be made
    // var    : variable for which the histogram will me made (for it's value on time t=t_{obs})

    // parameters buttons

    // ok button
    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("OK", QDialogButtonBox::AcceptRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &HistogramCreator::showHistogram);
    pMainLayout->addWidget(mpButtonBox, 0, Qt::AlignCenter);

    // Layout settings
    setLayout(pMainLayout);
}

void HistogramCreator::showHistogram()
{
    // Generate filename of png to fetch/generate, using the input parameters entered by the user
    QString fileName = resultsPath + "plots/zzz.png";

    // Check if PNG is available. If it is not, generate it
    QImageReader reader(fileName);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        makePNG(fileName);
    }
    else{
        ImageViewerDialog *pImageViewer = new ImageViewerDialog(fileName, this);
        pImageViewer->show();
    }
}

int HistogramCreator::makePNG(QString png_filename)
{
    // Get parameters
    QString scriptPathBaseDir = librariesPath;
    QString scriptPath = librariesPath + "callable_methods/plot_histogram.py";
    QString pythonBinPath = executablePath;

    // GENERATE COMMAND FROM SELECTED PARAMETERS
    QString command = pythonBinPath + " " + scriptPath;

    // TODO: Append parameter to command


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
