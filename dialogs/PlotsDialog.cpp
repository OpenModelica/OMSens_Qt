#include "dialogs/PlotsDialog.h"
#include <QVBoxLayout>
#include "../tabs/ParameterCombinationRunMap.h"
#include "functions/HistogramCreator.h"
#include "functions/ScatterPlotCreator.h"
#include "functions/LinesPlotVisualizer.h"


PlotsDialog::PlotsDialog(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *parent) : QDialog(parent)
{
    setMinimumWidth(410);
    setWindowTitle("Plots Tab");

    // Main Layout & Tab container
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QTabWidget *mpParametersContainer = new QTabWidget;

    // Initialize tabs
    // TAB: Parameters combinations => run (mapping summary)
    ParameterCombinationRunMap *params = new ParameterCombinationRunMap(mOMSensResultsPath);
    mpParametersContainer->addTab(params , tr("Parameters:run id"));

    // TAB: Scatter plotter
    ScatterPlotCreator *params3 = new ScatterPlotCreator(mPythonBinPath, mOMSensPath, mOMSensResultsPath);
    mpParametersContainer->addTab(params3 , tr("Scatter Plot"));

    // TAB: Histogram plotter
    HistogramCreator *params2 = new HistogramCreator(mPythonBinPath, mOMSensPath, mOMSensResultsPath);
    mpParametersContainer->addTab(params2 , tr("Histogram Plot"));

    LinesPlotVisualizer *params4 = new LinesPlotVisualizer(mPythonBinPath, mOMSensPath, mOMSensResultsPath);
    mpParametersContainer->addTab(params4 , tr("Line Plots"));

    // Layout settings
    mainLayout->addWidget(mpParametersContainer);
    mainLayout->setAlignment(Qt::AlignCenter);
    setLayout(mainLayout);
}
