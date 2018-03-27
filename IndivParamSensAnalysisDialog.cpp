#include "IndivParamSensAnalysisDialog.h"
#include "model.h"
#include "Util/Utilities.h"
#include <QMessageBox>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>

// BORRAR:
#include <iostream>
// BORRAR^

IndivParamSensAnalysisDialog::IndivParamSensAnalysisDialog(Model model,QWidget *pParent)
  : QDialog(pParent), model(model)
{
    // Function parameters
    const double max_target_time= 5000;
    const double max_perturbation_perc= 100;
    const double min_perturbation_perc= -100;
    // Indiv Param Analysis Information:
    const QVector<QString> methods( QVector<QString>()
                                   << "Relative"
                                   << "Root Mean Square");
    initializeWindowSettings();
    setHeading();
    initializeFormInputsAndLabels(min_perturbation_perc, max_perturbation_perc, max_target_time, methods);
    initializeButton();
    QGridLayout *pMainLayout = initializeLayout();
    addWidgetsToLayout(pMainLayout);
    // QWidget function to set layout to "this"
    setLayout(pMainLayout);
}


void IndivParamSensAnalysisDialog::initializeWindowSettings()
{
    setWindowTitle("Parameter Sensitivity Analysis - Individual Parameter Based Sensitivity Analysis");
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumWidth(550);
}

void IndivParamSensAnalysisDialog::setHeading()
{
    // set dialog heading
    mpHeading = Utilities::getHeadingLabel("Individual Parameter Based Sensitivity Analysis");
    // set separator line
    mpHorizontalLine = Utilities::getHeadingLine();
}

void IndivParamSensAnalysisDialog::initializeButton()
{
    // create OK button
    mpRunButton = new QPushButton("Ok");
    mpRunButton->setAutoDefault(true);
    connect(mpRunButton, SIGNAL(clicked()), SLOT(runIndivParamSensAnalysis()));
}

void IndivParamSensAnalysisDialog::initializeFormInputsAndLabels(const double min_perturbation_perc, const double max_perturbation_perc, const double max_target_time,  const QVector<QString> methods )
{
    // User inputs
    mpPercentageLabel = new Label(tr("Percentage:"));
    mpPercentageBox = new QDoubleSpinBox;
    mpPercentageBox->setRange(min_perturbation_perc, max_perturbation_perc);
    mpPercentageBox->setValue(5);
    mpPercentageBox->setSuffix("%");

    mpVariableLabel = new Label(tr("Target Variable:"));
    mpVariableComboBox = new QComboBox;
    QList<QString> outputVariables = model.getOutputVariables();
    for (int i_vars=0; i_vars<outputVariables.size(); i_vars++)
    {
        mpVariableComboBox->addItem(outputVariables[i_vars], QVariant(i_vars));
    }

    mpMethodLabel = new Label(tr("Method:"));
    mpMethodsButtonGroup = new QButtonGroup();
    mpRelRadio = new QRadioButton(tr(qPrintable(methods[0])),this);
    mpRelRadio->toggle(); //This method starts selected by default
    mpRMSRadio = new QRadioButton(tr(qPrintable(methods[1])),this);
    mpMethodsButtonGroup->addButton(mpRelRadio, 0);
    mpMethodsButtonGroup->addButton(mpRMSRadio, 1);

    mpTimeLabel = new Label(tr("Time:"));
    mpTimeBox = new QDoubleSpinBox;
    mpTimeBox->setRange(0, max_target_time);
    mpTimeBox->setValue(1);

}

QGridLayout * IndivParamSensAnalysisDialog::initializeLayout()
{
    // set grid layout
    QGridLayout *pMainLayout = new QGridLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    return pMainLayout;
}

void IndivParamSensAnalysisDialog::addWidgetsToLayout(QGridLayout *pMainLayout)
{
    pMainLayout->addWidget(mpHeading, 0, 0, 1, 3);
    pMainLayout->addWidget(mpHorizontalLine, 1, 0, 1, 3);
    pMainLayout->addWidget(mpPercentageLabel, 2, 0);
    pMainLayout->addWidget(mpPercentageBox, 2, 1);
    pMainLayout->addWidget(mpVariableLabel, 5, 0);
    pMainLayout->addWidget(mpVariableComboBox, 5, 1, 1, 2);
    pMainLayout->addWidget(mpMethodLabel, 6, 0);
    pMainLayout->addWidget(mpRelRadio, 6, 1);
    pMainLayout->addWidget(mpRMSRadio, 6, 2);
    pMainLayout->addWidget(mpTimeLabel, 7, 0);
    pMainLayout->addWidget(mpTimeBox, 7, 1);

    pMainLayout->addWidget(mpRunButton, 10, 0, 1, 3, Qt::AlignRight);
}


void IndivParamSensAnalysisDialog::runIndivParamSensAnalysis()
{
    std::cout << "Values chosen:" << std::endl;
    std::cout << " Percentage: " << mpPercentageBox->value() << std::endl;
    std::cout << " Variable i: " << mpVariableComboBox->currentIndex() << std::endl;
    std::cout << " Method i: " << mpMethodsButtonGroup->checkedId() << std::endl;
    std::cout << " Time: " << mpTimeBox->value() << std::endl;
    accept();
}

