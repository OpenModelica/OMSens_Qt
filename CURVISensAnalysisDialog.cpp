#include "CURVISensAnalysisDialog.h"
#include "utilities.h"
#include <QMessageBox>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>

// BORRAR:
#include <iostream>
// BORRAR^

CURVISensAnalysisDialog::CURVISensAnalysisDialog(QWidget *pParent) : QDialog(pParent)
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
    mpHeading = Utilities::getHeadingLabel("CURVI Sensitivity Analysis");
    // set separator line
    mpHorizontalLine = Utilities::getHeadingLine();
    // User inputs
    mpPercentageLabel = new Label(tr("Percentage:"));
    mpPercentageBox = new QDoubleSpinBox;
    mpPercentageBox->setRange(min_perturbation_perc, max_perturbation_perc);
    mpPercentageBox->setValue(5);
    mpPercentageBox->setSuffix("%");

    mpVariableLabel = new Label(tr("Variable:"));
    // The button group is purely backend specific. No effect on the GUI
    mpOptimTypeButtonGroup = new QButtonGroup();
    mpMaxRadio = new QRadioButton(tr("Maximization"),this);
    mpMaxRadio->toggle(); //This index start selected by default
    mpMinRadio = new QRadioButton(tr("Minimization"),this);
    mpOptimTypeButtonGroup->addButton(mpMaxRadio, 0);
    mpOptimTypeButtonGroup->addButton(mpMinRadio, 1);
    // The layout is purley GUI specific. No effect on the backend.
    mpOptimRadioLayout = new QVBoxLayout;
    ->addWidget(button1);

    mpVariableComboBox = new QComboBox;
    for (int i_vars=0; i_vars<modelVars.size(); i_vars++)
    {
        mpVariableComboBox->addItem(modelVars[i_vars], QVariant(i_vars));
    }

    mpIndexLabel = new Label(tr("Index:"));


    mpTimeLabel = new Label(tr("Time:"));
    mpTimeBox = new QDoubleSpinBox;
    mpTimeBox->setRange(0, max_target_time);
    mpTimeBox->setValue(1);

    // create OK button
    mpRunButton = new QPushButton("Ok");
    mpRunButton->setAutoDefault(true);
    connect(mpRunButton, SIGNAL(clicked()), SLOT(runCURVISensAnalysis()));
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
    pMainLayout->addWidget(mpMaxRadio, 6, 1);
    pMainLayout->addWidget(mpMinRadio, 6, 2);
    pMainLayout->addWidget(mpTimeLabel, 7, 0);
    pMainLayout->addWidget(mpTimeBox, 7, 1);

    pMainLayout->addWidget(mpRunButton, 10, 0, 1, 3, Qt::AlignRight);
    setLayout(pMainLayout);
}

void CURVISensAnalysisDialog::runCURVISensAnalysis()
{
    std::cout << "Values chosen:" << std::endl;
    std::cout << " Percentage: " << mpPercentageBox->text().toUtf8().constData() << std::endl;
    std::cout << " Variable i: " << mpVariableComboBox->currentIndex() << std::endl;
    std::cout << " Index i: " << mpOptimTypeButtonGroup->checkedId() << std::endl;
    std::cout << " Time: " << mpTimeBox->text().toUtf8().constData() << std::endl;
    accept();
}
