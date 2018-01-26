#include "DualLists.h"
#include "model.h"
#include "MultiParamSweepDialog.h"
#include "utilities.h"
#include <QGridLayout>

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
    QList<QString> parameters = model.getParameters();
    for (int i_params=0; i_params<parameters.size(); i_params++)
    {
        mpVarsToPlotDualLists->addItemToLeftList(parameters[i_params]);
    }
    mpParamsToSweepTable = new QTableWidget(1, 4, this);
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
