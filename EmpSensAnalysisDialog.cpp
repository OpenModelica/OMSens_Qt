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
    setWindowTitle("Parameter Sensitivity Analysis - Empirical Indices");
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumWidth(550);
    // set import heading
    mpHeading = Utilities::getHeadingLabel("Empirical Sensitivity Analysis");
    // set separator line
    mpHorizontalLine = Utilities::getHeadingLine();
    // User inputs
    mpPercentageLabel = new Label(tr("Percentage:"));
    mpPercentageBox = new QDoubleSpinBox;
    mpPercentageBox->setRange(min_perturbation_perc, max_perturbation_perc);
    mpPercentageBox->setValue(5);
    mpPercentageBox->setSuffix("%");

    mpVariableLabel = new Label(tr("Variable:"));
    mpVariableComboBox = new QComboBox;
    for (int i_vars=0; i_vars<modelVars.size(); i_vars++)
    {
        mpVariableComboBox->addItem(modelVars[i_vars], QVariant(i_vars));
    }

    mpIndexLabel = new Label(tr("Index:"));
    mpIndexComboBox = new QComboBox;
    for (int i_indices=0; i_indices<indices.size(); i_indices++)
    {
        mpIndexComboBox->addItem(indices[i_indices], QVariant(i_indices));
    }

    mpTimeLabel = new Label(tr("Time:"));
    mpTimeBox = new QDoubleSpinBox;
    mpTimeBox->setRange(0, max_target_time);
    mpTimeBox->setValue(1);

    // create OK button
    mpRunButton = new QPushButton("Ok");
    mpRunButton->setAutoDefault(true);
    connect(mpRunButton, SIGNAL(clicked()), SLOT(runEmpSensAnalysis()));
    // set grid layout
    QGridLayout *pMainLayout = new QGridLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    pMainLayout->addWidget(mpHeading, 0, 0, 1, 3);
    pMainLayout->addWidget(mpHorizontalLine, 1, 0, 1, 3);
    pMainLayout->addWidget(mpPercentageLabel, 2, 0);
    pMainLayout->addWidget(mpPercentageBox, 2, 1);
    pMainLayout->addWidget(mpVariableLabel, 5, 0);
    pMainLayout->addWidget(mpVariableComboBox, 5, 1, 1, 2);
    pMainLayout->addWidget(mpIndexLabel, 6, 0);
    pMainLayout->addWidget(mpIndexComboBox, 6, 1, 1, 2);
    pMainLayout->addWidget(mpTimeLabel, 7, 0);
    pMainLayout->addWidget(mpTimeBox, 7, 1);

    pMainLayout->addWidget(mpRunButton, 10, 0, 1, 3, Qt::AlignRight);
    setLayout(pMainLayout);
}

void EmpSensAnalysisDialog::runEmpSensAnalysis()
{
    std::cout << "Values chosen:" << std::endl;
    std::cout << " Percentage: " << mpPercentageBox->text().toUtf8().constData() << std::endl;
    std::cout << " Variable i: " << mpVariableComboBox->currentIndex() << std::endl;
    std::cout << " Index i: " << mpIndexComboBox->currentIndex() << std::endl;
    std::cout << " Time: " << mpTimeBox->text().toUtf8().constData() << std::endl;
    accept();
}

