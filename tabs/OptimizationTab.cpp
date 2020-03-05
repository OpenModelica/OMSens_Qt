#include "OptimizationTab.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QtMath>
#include <QFileDialog>

OptimizationTab::OptimizationTab(QList<QString> variables, QString target_var, double epsilon, double percentage, bool maximize, QWidget *parent) : QWidget(parent)
{
    // Auxiliary : Horizontal line
    mpHorizontalLine = new QFrame;
    mpHorizontalLine->setFrameShape(QFrame::HLine);
    mpHorizontalLine->setFrameShadow(QFrame::Sunken);

    // Variables
    mpVariablesLabel = new QLabel(tr("Variable:"), this);
    mpVariablesComboBox = new QComboBox(this);
    foreach(QString var_name, variables) {
        mpVariablesComboBox->addItem(var_name);
    }
    int target_var_index = mpVariablesComboBox->findText(target_var);
    mpVariablesComboBox->setCurrentIndex(target_var_index);

    // Goal
    mpGoalButtonGroup = new QButtonGroup(this); // Has to have "this" as parent because it's never assigned to anything
    mpMinRadio = new QRadioButton(tr("Minimize"));
    mpMaxRadio = new QRadioButton(tr("Maximize"));
    toggleOptimType(maximize);
    mpGoalButtonGroup->addButton(mpMinRadio, mMinimizeButtonId);
    mpGoalButtonGroup->addButton(mpMaxRadio, mMaximizeButtonId);

    // Epsilon
    mpEpsilonLabel = new QLabel(tr("Epsilon"));
    mpEpsilonBox = new SciNotationDoubleSpinbox;
    mpEpsilonBox->setRange(std::numeric_limits<double>::min(), 1-std::numeric_limits<double>::min());
    mpEpsilonBox->setValue(epsilon);
    mpEpsilonBox->setSingleStep(0.01);
    mpEpsilonHintLabel = new QLabel(tr("(0 < ε < 1)"));

    // Boundaries
    mpBoundariesLabel = new QLabel(tr("Perturbation boundaries:"));
    mpBoundariesBox = new QDoubleSpinBox;
    mpBoundariesBox->setRange(0.01, std::numeric_limits<double>::max());
    mpBoundariesBox->setValue(percentage);
    mpBoundariesBox->setPrefix("±");
    mpBoundariesBox->setSuffix("%");

    // Layout
    QVBoxLayout *pMainLayout = new QVBoxLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // Optimizer
    // TODO: read optional optimizers from somewhere (config file?)
    mpOptimizerNameLabel = new QLabel(tr("Optimizer Name"));
    mpOptimizerNameComboBox = new QComboBox(this);
    mpOptimizerNameComboBox->addItem("CURVIF");
    mpOptimizerNameComboBox->addItem("CURVIFGR");
    pMainLayout->addWidget(mpOptimizerNameLabel);
    pMainLayout->addWidget(mpOptimizerNameComboBox);

    // Objective function
    mpObjectiveFunctionNameLabel = new QLabel(tr("Objective function name"));
    mpObjectiveFunctionNameComboBox = new QComboBox(this);
    mpObjectiveFunctionNameComboBox->addItem("Alpha weighted path constrained");
    mpObjectiveFunctionNameComboBox->addItem("Single variable");
    pMainLayout->addWidget(mpObjectiveFunctionNameLabel);
    pMainLayout->addWidget(mpObjectiveFunctionNameComboBox);

    // Parameters for objective function (alpha weighted optimization)
    // TODO: read optional objective functions from somewhere (config file?)
    mpAlphaLabel = new QLabel(tr("Alpha weighted optimization: set alpha value (α)"));
    mpAlphaValue = new QDoubleSpinBox;
    mpAlphaValue->setRange(0, 1);
    mpAlphaValue->setValue(0.5);
    mpAlphaValue->setSingleStep(0.05);

    pMainLayout->addWidget(mpHorizontalLine);
    pMainLayout->addWidget(mpAlphaLabel);
    pMainLayout->addWidget(mpAlphaValue);

    pMainLayout->addWidget(mpHorizontalLine);

    // Parameters for objective function (single variable optimization)
    mpSingleVariableOptimizationLabel = new QLabel(tr("Single variable optimization: set objective variable name"));
    pMainLayout->addWidget(mpSingleVariableOptimizationLabel);
    QGridLayout *gridLayout = new QGridLayout;

    // Variables
    gridLayout->addWidget(mpVariablesLabel   ,0,0);
    gridLayout->addWidget(mpVariablesComboBox,0,1);
    gridLayout->addWidget(mpMinRadio         ,0,2);
    gridLayout->addWidget(mpMaxRadio         ,0,3);
    // Epsilon
    gridLayout->addWidget(mpEpsilonLabel    ,2,0);
    gridLayout->addWidget(mpEpsilonBox      ,2,1);
    gridLayout->addWidget(mpEpsilonHintLabel,2,2);
    // Boundaries
    gridLayout->addWidget(mpBoundariesLabel,3,0);
    gridLayout->addWidget(mpBoundariesBox  ,3,1);
    // Add grid layout
    pMainLayout->addLayout(gridLayout);

    // Directory of path constrained condition
    pMainLayout->addWidget(mpHorizontalLine);

    mpConstrainedPathLabel = new QLabel(tr("Constrained path file path"));
    pMainLayout->addWidget(mpConstrainedPathLabel);

    QString defaultLimitedPathFolderPath = "/home/omsens/limit_path.csv";

    // TODO: allow manual input of constrain path (optional to csv file)
    mpLimitedPathFolderLabel = new QLabel(tr("Constrained Path File directory path"));
    mpLimitedPathFolderValue = new QLabel(defaultLimitedPathFolderPath);
    mpLimitedPathFolderValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mpChooseCSVFileButton = new QPushButton("Choose folder");
    mpChooseCSVFileButton->setAutoDefault(true);
    mpChooseCSVFileButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpChooseCSVFileButton, SIGNAL(clicked()), this, SLOT(launchChooseCSVFileDialog()));

    QHBoxLayout *pLimitedPathFolderRowLayout = new QHBoxLayout;
    pLimitedPathFolderRowLayout->addWidget(mpLimitedPathFolderValue);
    pLimitedPathFolderRowLayout->addWidget(mpChooseCSVFileButton);
    pMainLayout->addLayout(pLimitedPathFolderRowLayout);

    // Layout settings
    setLayout(pMainLayout);
}

void OptimizationTab::launchChooseCSVFileDialog()
{
    // Launch dialog
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose File Path (*.csv)"),
                                                 "/home");
    // Save path into member variable
    mpLimitedPathFolderValue->setText(filename);
}


// Getters
QString OptimizationTab::getOptimizerName() const
{
    return mpOptimizerNameComboBox->currentText();
}
QString OptimizationTab::getObjectiveFunctionName() const
{
    return mpObjectiveFunctionNameComboBox->currentText();
}
double OptimizationTab::getAlphaValue() const
{
    return mpAlphaValue->value();
}
QString OptimizationTab::getConstrainedTimePathFile() const
{
    return mpLimitedPathFolderValue->text();
}


double OptimizationTab::getEpsilon() const
{
    return mpEpsilonBox->value();
}
QString OptimizationTab::getTargetVariable() const
{
    return mpVariablesComboBox->currentText();
}

int OptimizationTab::getGoalId() const
{
    return mpGoalButtonGroup->checkedId();
}


double OptimizationTab::getBoundariesValue() const
{
    return mpBoundariesBox->value();
}

void OptimizationTab::toggleOptimType(bool maximize)
{
    if(maximize)
    {
        mpMaxRadio->toggle();
    }
    else
    {
        mpMinRadio->toggle();
    }
}
