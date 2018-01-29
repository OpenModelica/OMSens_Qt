#include "DualLists.h"
#include "model.h"
#include "MultiParamSweepDialog.h"
#include "utilities.h"
#include <QGridLayout>
#include <QHeaderView>
#include <QSizePolicy>

MultiParamSweepDialog::MultiParamSweepDialog(Model model, QWidget *pParent) :
    QDialog(pParent), model(model)
{
    // Function parameters
    const double defaultTime= 2000;
    const double maxTargetTime= 5000;

    initializeWindowSettings();
    setHeading();
    // Initialize Form Inputs and Labels
    mpStopTimeLabel = new Label(tr("Time:"));
    mpStopTimeBox = new QDoubleSpinBox;
    mpStopTimeBox->setRange(0, maxTargetTime);
    mpStopTimeBox->setValue(defaultTime);
    mpVarsToPlotLabel = new Label(tr("Variables to plot:"));
    mpVarsToPlotDualLists = new DualLists;
    QList<QString> variables = model.getOutputVariables();
    for (int i_params=0; i_params<variables.size(); i_params++)
    {
        mpVarsToPlotDualLists->addItemToLeftList(variables[i_params]);
    }
    mpParamsToSweepLabel = new Label(tr("Parameters to sweep:"));
    mpParamsToSweepTable = new QTableWidget(0, 3);
    const QList<QString> tableHeaders( QList<QString>()
                                     << "Parameter Name"
                                     << "#iterations"
                                     << "Perturbation");
    mpParamsToSweepTable->setHorizontalHeaderLabels(tableHeaders);
    // Hide grid
    mpParamsToSweepTable->setShowGrid(false);
    // Resize columns to contents
    mpParamsToSweepTable->resizeColumnsToContents();
    // Disable scrollbars
    mpParamsToSweepTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mpParamsToSweepTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Settings with QHeaderView:
    QHeaderView *headerView = mpParamsToSweepTable->verticalHeader();
    // Hide line counter
    headerView->setVisible(false);

    // Add a row with valid values as an example
    // Add "blank" row
    const int rowNum = 0;
    mpParamsToSweepTable->insertRow(rowNum);
    // Create parameters combobox
    QComboBox *parametersComboBox = new QComboBox;
    QList<QString> parameters = model.getParameters();
    for (int i_parameters=0; i_parameters<parameters.size(); i_parameters++)
    {
        parametersComboBox->addItem(parameters[i_parameters], QVariant(i_parameters));
    }
    // Add params combobox
    int paramsColNum = 0;
    mpParamsToSweepTable->setCellWidget(rowNum,paramsColNum,parametersComboBox);
    // Create #iterations spinbox
    const double maxNumberOfIterations= 50000;
    QSpinBox *iterationsSpinBox = new QSpinBox;
    iterationsSpinBox->setRange(0,maxNumberOfIterations);
    iterationsSpinBox->setValue(1);
    iterationsSpinBox->setAlignment(Qt::AlignRight);
    // Add iterations spinbox
    int numberOfIterationsColNum = 1;
    mpParamsToSweepTable->setCellWidget(rowNum,numberOfIterationsColNum,iterationsSpinBox);
    // Create perturbation spinbox
    const double minPerturbationPercentage= -100;
    const double maxPerturbationPercentage= 100;
    QDoubleSpinBox *perturbationSpinBox = new QDoubleSpinBox;
    perturbationSpinBox->setRange(minPerturbationPercentage, maxPerturbationPercentage);
    perturbationSpinBox->setValue(5);
    perturbationSpinBox->setSuffix("%");
    perturbationSpinBox->setAlignment(Qt::AlignRight);
    // Add perturbation spinbox
    int perturbationColNum = 2;
    mpParamsToSweepTable->setCellWidget(rowNum,perturbationColNum,perturbationSpinBox);

    // Resize table depending on number of rows and cols
    // Get widths, lengths and heights from table headers
    const int verticalHeaderWidth    = mpParamsToSweepTable->verticalHeader()->width();
    const int verticalHeaderLength   = mpParamsToSweepTable->verticalHeader()->length();
    const int horizontalHeaderLength = mpParamsToSweepTable->horizontalHeader()->length();
    const int horizontalHeaderHeight = mpParamsToSweepTable->horizontalHeader()->height();

    // Define paddings
    const int widthPadding  = 0;
    const int heightPadding = 0;

    // Set final widths and heights
    const int tableWidth  = horizontalHeaderLength + verticalHeaderWidth    + widthPadding;
    const int tableHeight = verticalHeaderLength   + horizontalHeaderHeight + heightPadding;
    mpParamsToSweepTable->setFixedSize(tableWidth,tableHeight);

    // Create time label and form
    mpTimeLabel = new Label(tr("Time:"));
    mpTimeBox = new QDoubleSpinBox;
    mpTimeBox->setRange(0, maxTargetTime);
    mpTimeBox->setValue(defaultTime);

    // create OK button
    initializeButton();
    // set grid layout
    QGridLayout *pMainLayout = initializeLayout();
    addWidgetsToLayout(pMainLayout);
    // QWidget function to set layout to "this"
    setLayout(pMainLayout);
}

void MultiParamSweepDialog::initializeWindowSettings()
{
    setWindowTitle("Parameter Sensitivity Analysis - Empirical Indices");
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumWidth(550);
}

void MultiParamSweepDialog::setHeading()
{
    // set dialog heading
    mpHeading = Utilities::getHeadingLabel("Multi-parameter sweep");
    // set separator line
    mpHorizontalLine = Utilities::getHeadingLine();
}

QGridLayout * MultiParamSweepDialog::initializeLayout()
{
    QGridLayout *pMainLayout = new QGridLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    return pMainLayout;
}

void MultiParamSweepDialog::addWidgetsToLayout(QGridLayout *pMainLayout)
{
    pMainLayout->addWidget(mpHeading, 0, 0, 1, 3);
    pMainLayout->addWidget(mpHorizontalLine, 1, 0, 1, 3);
    pMainLayout->addWidget(mpVarsToPlotLabel, 2, 0);
    pMainLayout->addWidget(mpVarsToPlotDualLists, 2, 1, 1, 3);
    pMainLayout->addWidget(mpParamsToSweepLabel, 3, 0);
    pMainLayout->addWidget(mpParamsToSweepTable, 3, 1, 1, 3);
    pMainLayout->addWidget(mpTimeLabel, 4, 0);
    pMainLayout->addWidget(mpTimeBox, 4, 1);
    pMainLayout->addWidget(mpRunButton, 10, 0, 1, 3, Qt::AlignRight);
}

void MultiParamSweepDialog::initializeButton()
{
    mpRunButton = new QPushButton("Ok");
    mpRunButton->setAutoDefault(true);
    connect(mpRunButton, SIGNAL(clicked()), this, SLOT(runMultiParamSweep()));
}


void MultiParamSweepDialog::runMultiParamSweep()
{
    accept();
}
