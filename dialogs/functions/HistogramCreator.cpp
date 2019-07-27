#include "HistogramCreator.h"
#include <QProcess>
#include <QProgressBar>
#include <QProgressDialog>
#include <QDateTime>
#include <QVBoxLayout>

HistogramCreator::HistogramCreator(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *pParent) : QDialog(pParent)
{
    executablePath = mPythonBinPath;
    librariesPath  = mOMSensPath;
    resultsPath    = mOMSensResultsPath;

    // Dialog settings
    setMinimumWidth(410);
    setWindowTitle("Histogram Creator");

    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("OK", QDialogButtonBox::AcceptRole);

    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &HistogramCreator::makeHistogram);

    QVBoxLayout *pMainLayout = new QVBoxLayout;

    // Accept button
    pMainLayout->addWidget(mpButtonBox, 0, Qt::AlignCenter);

    // Layout settings
    setLayout(pMainLayout);
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

int HistogramCreator::makeHistogram()
{
    QProcess pythonScriptProcess;

    QString scriptPathBaseDir = librariesPath;
    // "/home/omsens/Documents/OMSens/";

    QString scriptPath = librariesPath + "callable_methods/plot_histogram.py";
    // "/home/omsens/Documents/OMSens/callable_methods/plot_histogram.py";

    QString pythonBinPath = executablePath;
    //"/home/omsens/anaconda3/bin/python";

    QString command = pythonBinPath + " " + scriptPath;

    // Set working dir path
    pythonScriptProcess.setWorkingDirectory(scriptPathBaseDir);

    // Initialize dialog showing progress
    QString progressDialogText = progressDialogTextForCurrentTime();
    QProgressDialog *dialog = new QProgressDialog(progressDialogText, "Cancel", 0, 0, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    connect(&pythonScriptProcess, SIGNAL(finished(int)), dialog, SLOT(close()));

    // Connect dialog "cancel"  with command kill
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
