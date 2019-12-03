#include "HistogramCreator.h"
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

using namespace std;

HistogramCreator::HistogramCreator(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *pParent) : QDialog(pParent)
{
    executablePath = mPythonBinPath;
    librariesPath  = mOMSensPath;
    resultsPath    = mOMSensResultsPath;

    // Dialog settings
    setMinimumWidth(410);
    setWindowTitle("Histogram Creator");

    CSVReader *csv_reader = new CSVReader();
    // TODO: for reuse in different contexts (apart from multiparameter sweep), these 3 files must be generated!
    QVector<QString> parameters = csv_reader->getColumnsNames(mOMSensResultsPath + "/" + "results/" + "parameters_run.csv");
    QVector<QString> variables = csv_reader->getColumnsNames(mOMSensResultsPath + "/" + "results/" + "variables.csv");
    QVector<double> time_values = csv_reader->getColumnValues(mOMSensResultsPath + "/" + "results/runs/std_run.csv", "time");


    // Layout
    QVBoxLayout *pMainLayout = new QVBoxLayout;

    // Time value
    int precisionVal = 3;
    double min = time_values[0];
    double max = time_values[time_values.size() - 1];
    QString min_str = QString::fromStdString(std::to_string(min).substr(0, std::to_string(min).find(".") + precisionVal + 1));
    QString max_str = QString::fromStdString(std::to_string(max).substr(0, std::to_string(max).find(".") + precisionVal + 1));
    QString str = "Time: (Min=" + min_str + ", Max=" + max_str + ")";
    QLabel *time_label = new QLabel(str);
    options_time_box = new QLineEdit;
    options_time_box->setText(max_str);
    QHBoxLayout *row1 = new QHBoxLayout;
    row1->addWidget(time_label);
    row1->addWidget(options_time_box);

    // Show histogram for variable
    QLabel *options_variables_label = new QLabel("Variables (init vs. end): ");
    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("One variable (init vs. end)", QDialogButtonBox::AcceptRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &HistogramCreator::showHistogramVariable);
    options_variables_box = new QComboBox;
    for (QString varName: variables) {
        options_variables_box->addItem(varName);
    }
    QHBoxLayout *row2 = new QHBoxLayout;
    row2->addWidget(options_variables_label);
    row2->addWidget(options_variables_box);
    row2->addWidget(mpButtonBox);

    // Show historam for parameter
    QLabel *options_parameters_label_parameter = new QLabel("Parameter: ");
    QLabel *options_parameters_label_variable = new QLabel("Variable: ");
    options_parameters_box = new QComboBox;
    for (QString parameterName : parameters) {
        if (parameterName != "run_id") options_parameters_box->addItem(parameterName);
    }
    options_variables_box_2 = new QComboBox;
    for (QString variableName : variables) {
        options_variables_box_2->addItem(variableName);
    }
    QDialogButtonBox *mpButtonBoxParameters = new QDialogButtonBox;
    mpButtonBoxParameters->addButton("One Parameter / One variable", QDialogButtonBox::AcceptRole);
    connect(mpButtonBoxParameters, &QDialogButtonBox::accepted, this, &HistogramCreator::showHistogramParameter);
    QHBoxLayout *row3 = new QHBoxLayout;
    row3->addWidget(options_parameters_label_parameter);
    row3->addWidget(options_parameters_box);
    row3->addWidget(options_parameters_label_variable);
    row3->addWidget(options_variables_box_2);
    row3->addWidget(mpButtonBoxParameters);

    // Layout settings
    pMainLayout->addItem(row1);
    pMainLayout->addItem(row3);
    pMainLayout->addItem(row2);
    setLayout(pMainLayout);
}

void HistogramCreator::showHistogramParameter()
{
    QString fileNamePath = resultsPath + "/results/" + "plots/"
            + "hp"
            + "_" + options_time_box->text()
            + "_" + options_parameters_box->currentText()
            + ".png";

    QString args = "--filename_path=" + fileNamePath
            + " " + "--parameter=" + options_parameters_box->currentText()
            + " " + "--variable=" + options_variables_box->currentText()
            + " " + "--time_value=" + options_time_box->text()
            + " " + "--results_path=" + resultsPath;

    // Check if PNG is available. If it is not, generate it
    QImageReader reader(fileNamePath);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        makePNG(args);
    }
    ImageViewerDialog *pImageViewer = new ImageViewerDialog(fileNamePath, this);
    pImageViewer->show();
}

void HistogramCreator::showHistogramVariable()
{
    QString fileNamePath = resultsPath + "/results/" + "plots/"
            + "hv"
            + "_" + options_time_box->text()
            + "_" + options_variables_box->currentText()
            + ".png";

    QString args = "--filename_path=" + fileNamePath
            + " " + "--variable=" + options_variables_box->currentText()
            + " " + "--time_value=" + options_time_box->text()
            + " " + "--results_path=" + resultsPath;

    // Check if PNG is available. If it is not, generate it
    QImageReader reader(fileNamePath);
    const QImage newImage = reader.read();
    bool image_available = true;
    if (newImage.isNull()) {
        image_available = makePNG(args);
    }
    if(image_available) {
        ImageViewerDialog *pImageViewer = new ImageViewerDialog(fileNamePath, this);
        pImageViewer->show();
    }
}

int HistogramCreator::makePNG(QString args)
{
    // Get parameters
    QString scriptPathBaseDir = librariesPath;
    QString scriptPath        = librariesPath + "callable_methods/plot_histogram.py";
    QString pythonBinPath     = executablePath;

    // RUN PROCESS
    QString command = pythonBinPath + " " + scriptPath + " " + args;
//    QString command = "/home/omsens/anaconda3/bin/python /home/omsens/Documents/OMSens/callable_methods/plot_histogram.py --filename_path=/home/omsens/Documents/results_experiments/sweep_results/2019-08-05/14_25_27/results/plots/hv__pred_pop.png --parameter=alpha --variable=pred_pop --time_value= --results_path=/home/omsens/Documents/results_experiments/sweep_results/2019-08-05/14_25_27";

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

    if(!processEndedCorrectly) {
        QString error_string(pythonScriptProcess.readAllStandardError());
        QMessageBox msg;
        msg.setText("ERROR: \n" + error_string);
        msg.exec();
    }
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
