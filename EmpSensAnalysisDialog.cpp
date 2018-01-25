#include "EmpSensAnalysisDialog.h"
#include "utilities.h"
#include <QMessageBox>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>

// BORRAR:
#include <iostream>
// BORRAR^

EmpSensAnalysisDialog::EmpSensAnalysisDialog(QWidget *pParent)
  : QDialog(pParent)
{
    // Function parameters
    const double max_target_time= 5000;
    const double max_perturbation_perc= 100;
    const double min_perturbation_perc= -100;
    // Model information:
    const QVector<QString> modelVars( QVector<QString>()
                                   << "population"
                                   << "nr_resources"
                                   << "human_welfare_index");
    // Emp Analysis Information:
    const QVector<QString> indices( QVector<QString>()
                                   << "Relative index"
                                   << "Root Mean Square index");
    initializeWindowSettings();
    setHeading();
    initializeFormInputsAndLabels(min_perturbation_perc, modelVars, max_perturbation_perc, max_target_time);
    initializeButton();
    QGridLayout *pMainLayout = initializeLayout();
    addWidgetsToLayout(pMainLayout);
    // QWidget function to set layout to "this"
    setLayout(pMainLayout);
}


void EmpSensAnalysisDialog::initializeWindowSettings()
{
    setWindowTitle("Parameter Sensitivity Analysis - Empirical Indices");
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumWidth(550);
}

void EmpSensAnalysisDialog::setHeading()
{
    // set dialog heading
    mpHeading = Utilities::getHeadingLabel("Empirical Sensitivity Analysis");
    // set separator line
    mpHorizontalLine = Utilities::getHeadingLine();
}

void EmpSensAnalysisDialog::initializeButton()
{
    // create OK button
    mpRunButton = new QPushButton("Ok");
    mpRunButton->setAutoDefault(true);
    connect(mpRunButton, SIGNAL(clicked()), SLOT(runEmpSensAnalysis()));
}

void EmpSensAnalysisDialog::initializeFormInputsAndLabels(const double min_perturbation_perc, const QVector<QString> modelVars, const double max_perturbation_perc, const double max_target_time)
{
    // User inputs
    mpPercentageLabel = new Label(tr("Percentage:"));
    mpPercentageBox = new QDoubleSpinBox;
    mpPercentageBox->setRange(min_perturbation_perc, max_perturbation_perc);
    mpPercentageBox->setValue(5);
    mpPercentageBox->setSuffix("%");

    mpVariableLabel = new Label(tr("Target Variable:"));
    mpVariableComboBox = new QComboBox;
    for (int i_vars=0; i_vars<modelVars.size(); i_vars++)
    {
        mpVariableComboBox->addItem(modelVars[i_vars], QVariant(i_vars));
    }

    mpIndexLabel = new Label(tr("Index:"));
    mpIndicesButtonGoup = new QButtonGroup();
    mpRelRadio = new QRadioButton(tr("Relative Index"),this);
    mpRelRadio->toggle(); //This index start selected by default
    mpRMSRadio = new QRadioButton(tr("Root Mean Square Index"),this);
    mpIndicesButtonGoup->addButton(mpRelRadio, 0);
    mpIndicesButtonGoup->addButton(mpRMSRadio, 1);

    mpTimeLabel = new Label(tr("Time:"));
    mpTimeBox = new QDoubleSpinBox;
    mpTimeBox->setRange(0, max_target_time);
    mpTimeBox->setValue(1);

}

QGridLayout * EmpSensAnalysisDialog::initializeLayout()
{
    // set grid layout
    QGridLayout *pMainLayout = new QGridLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    return pMainLayout;
}

void EmpSensAnalysisDialog::addWidgetsToLayout(QGridLayout *pMainLayout)
{
    pMainLayout->addWidget(mpHeading, 0, 0, 1, 3);
    pMainLayout->addWidget(mpHorizontalLine, 1, 0, 1, 3);
    pMainLayout->addWidget(mpPercentageLabel, 2, 0);
    pMainLayout->addWidget(mpPercentageBox, 2, 1);
    pMainLayout->addWidget(mpVariableLabel, 5, 0);
    pMainLayout->addWidget(mpVariableComboBox, 5, 1, 1, 2);
    pMainLayout->addWidget(mpIndexLabel, 6, 0);
    pMainLayout->addWidget(mpRelRadio, 6, 1);
    pMainLayout->addWidget(mpRMSRadio, 6, 2);
    pMainLayout->addWidget(mpTimeLabel, 7, 0);
    pMainLayout->addWidget(mpTimeBox, 7, 1);

    pMainLayout->addWidget(mpRunButton, 10, 0, 1, 3, Qt::AlignRight);
}


void EmpSensAnalysisDialog::runEmpSensAnalysis()
{
    std::cout << "Values chosen:" << std::endl;
    std::cout << " Percentage: " << mpPercentageBox->cleanText().toUtf8().constData() << std::endl;
    std::cout << " Variable i: " << mpVariableComboBox->currentIndex() << std::endl;
    std::cout << " Index i: " << mpIndicesButtonGoup->checkedId() << std::endl;
    std::cout << " Time: " << mpTimeBox->text().toUtf8().constData() << std::endl;
    accept();
}

