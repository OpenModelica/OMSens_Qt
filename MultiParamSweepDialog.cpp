#include "DualLists.h"
#include "model.h"
#include "MultiParamSweepDialog.h"
#include "utilities.h"
#include <QGridLayout>
#include <QHeaderView>
#include <QSizePolicy>

// BORRAR:
#include <iostream>
// BORRAR^

MultiParamSweepDialog::MultiParamSweepDialog(Model model, QWidget *pParent) :
    QDialog(pParent), model(model)
{
    // Function parameters
    const double defaultTime= 2000;
    const double maxTargetTime= 5000;
    const int maxNumberOfIterations= 50000;
    const double minPerturbationPercentage= -100;
    const double maxPerturbationPercentage= 100;

    initializeWindowSettings();
    setHeading();
    initializeFormInputsAndLabels(defaultTime, maxTargetTime, model, minPerturbationPercentage, maxPerturbationPercentage, maxNumberOfIterations);

    // create OK button
    initializeButton();

    // set grid layout
    QGridLayout *pMainLayout = initializeLayout();
    addWidgetsToLayout(pMainLayout);
    // QWidget function to set layout to "this"
    setLayout(pMainLayout);
}

void MultiParamSweepDialog::initializeVarsToPlotForms(Model model)
{
    mpVarsToPlotLabel = new Label(tr("Variables to plot:"));
    mpVarsToPlotDualLists = new DualLists;
    QList<QString> variables = model.getOutputVariables();
    for (int i_params=0; i_params<variables.size(); i_params++)
    {
        mpVarsToPlotDualLists->addItemToLeftList(variables[i_params]);
    }
}

void MultiParamSweepDialog::initializeParamsToSweepLabel()
{
    mpParamsToSweepLabel = new Label(tr("Parameters to sweep:"));
}

void MultiParamSweepDialog::setParamsTableHeaders()
{
    mpParamsToSweepTable = new QTableWidget(0, 4);
    const QList<QString> tableHeaders( QList<QString>()
                                     << "Parameter Name"
                                     << "#iterations"
                                     << "Perturbation"
                                     << "");
    mpParamsToSweepTable->setHorizontalHeaderLabels(tableHeaders);
}

void MultiParamSweepDialog::setParamsTableSettings()
{
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
}

void MultiParamSweepDialog::addParamsComboBoxToTable(const int rowNum, Model model)
{
    QComboBox *pParametersComboBox = new QComboBox;
    QList<QString> parameters = model.getParameters();
    for (int i_parameters=0; i_parameters<parameters.size(); i_parameters++)
    {
        pParametersComboBox->addItem(parameters[i_parameters], QVariant(i_parameters));
    }
    // Add params combobox
    mpParamsToSweepTable->setCellWidget(rowNum,paramsColNum,pParametersComboBox);
}

void MultiParamSweepDialog::addIterationsSpinBoxToTable(const int rowNum, const int maxNumberOfIterations)
{
    QSpinBox *pIterationsSpinBox = new QSpinBox;
    pIterationsSpinBox->setRange(0,maxNumberOfIterations);
    pIterationsSpinBox->setValue(1);
    pIterationsSpinBox->setAlignment(Qt::AlignRight);
    // Add iterations spinbox
    mpParamsToSweepTable->setCellWidget(rowNum,numberOfIterationsColNum,pIterationsSpinBox);
}

void MultiParamSweepDialog::addPerturbSpinBoxToTable(const double minPerturbationPercentage, const double maxPerturbationPercentage, const int rowNum)
{
    QDoubleSpinBox *pPerturbationSpinBox = new QDoubleSpinBox;
    pPerturbationSpinBox->setRange(minPerturbationPercentage, maxPerturbationPercentage);
    pPerturbationSpinBox->setValue(5);
    pPerturbationSpinBox->setSuffix("%");
    pPerturbationSpinBox->setAlignment(Qt::AlignRight);
    // Add perturbation spinbox
    mpParamsToSweepTable->setCellWidget(rowNum,perturbationColNum,pPerturbationSpinBox);
}

void MultiParamSweepDialog::addExampleRowToParamsTable(Model model, const double minPerturbationPercentage, const double maxPerturbationPercentage, const int maxNumberOfIterations)
{
    // Row index to add row to
    const int rowNum = 0;

    // Add "blank" row
    mpParamsToSweepTable->insertRow(rowNum);

    // Edit blank row with custom widgets in its cells
    addParamsComboBoxToTable(rowNum, model);
    addIterationsSpinBoxToTable(rowNum, maxNumberOfIterations);
    // Create perturbation spinbox
    addPerturbSpinBoxToTable(minPerturbationPercentage, maxPerturbationPercentage, rowNum);
    // Create a "Remove button" for this row
    QPushButton* pRemoveRowButton = new QPushButton();
    pRemoveRowButton->setText("X");
    connect(pRemoveRowButton, SIGNAL(clicked()), this, SLOT(removeRowSlot()));
    // Add remove row button to table
    mpParamsToSweepTable->setCellWidget(rowNum,removeRowButtonColNum,pRemoveRowButton);
}
void MultiParamSweepDialog::resizeParamsTable()
{
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
}

void MultiParamSweepDialog::initializeParamsToSweepForms(Model model, const double minPerturbationPercentage, const double maxPerturbationPercentage, const int maxNumberOfIterations)
{
    // We represent the form as a table and give the user the option to add new rows
    //   representing new params to sweep
    initializeParamsToSweepLabel();
    setParamsTableHeaders();
    setParamsTableSettings();

    // Add a row with valid values as an example for the user
    addExampleRowToParamsTable(model,minPerturbationPercentage,maxPerturbationPercentage,maxNumberOfIterations);
    addExampleRowToParamsTable(model,minPerturbationPercentage,maxPerturbationPercentage,maxNumberOfIterations);
    addExampleRowToParamsTable(model,minPerturbationPercentage,maxPerturbationPercentage,maxNumberOfIterations);

    resizeParamsTable();
}

void MultiParamSweepDialog::initializeStopTimeForms(const double maxTargetTime, const double defaultTime)
{
    mpStopTimeLabel = new Label(tr("Time:"));
    mpStopTimeBox = new QDoubleSpinBox;
    mpStopTimeBox->setRange(0, maxTargetTime);
    mpStopTimeBox->setValue(defaultTime);
}

void MultiParamSweepDialog::initializeFormInputsAndLabels(const double defaultTime, const double maxTargetTime, Model model, const double minPerturbationPercentage, const double maxPerturbationPercentage, const int maxNumberOfIterations)
{
    initializeVarsToPlotForms(model);
    initializeParamsToSweepForms(model, minPerturbationPercentage, maxPerturbationPercentage,maxNumberOfIterations);
    initializeStopTimeForms(maxTargetTime, defaultTime);
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
    pMainLayout->addWidget(mpStopTimeLabel, 4, 0);
    pMainLayout->addWidget(mpStopTimeBox, 4, 1);
    pMainLayout->addWidget(mpRunButton, 10, 0, 1, 3, Qt::AlignRight);
}

void MultiParamSweepDialog::initializeButton()
{
    mpRunButton = new QPushButton("Ok");
    mpRunButton->setAutoDefault(true);
    connect(mpRunButton, SIGNAL(clicked()), this, SLOT(runMultiParamSweep()));
}

// Slots:

void MultiParamSweepDialog::runMultiParamSweep()
{
    accept();
}

void MultiParamSweepDialog::removeRowSlot()
{
    QPushButton  *pClickedButton = qobject_cast<QPushButton *>(sender());
    for(int i = 0; i < mpParamsToSweepTable->rowCount(); i++)
    {
        if(pClickedButton == mpParamsToSweepTable->cellWidget(i,removeRowButtonColNum))
        {
            mpParamsToSweepTable->removeRow(i);
        }
    }
}
