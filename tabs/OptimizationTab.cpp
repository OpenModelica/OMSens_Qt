#include "OptimizationTab.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QtMath>
#include <QFileDialog>
#include <vector>
#include <algorithm>
#include <string>

OptimizationTab::OptimizationTab(QList<QString> variables, QString target_var, double epsilon,
                                 double percentage, bool maximize,
                                 QString optimizer_name, QString objective_function_name, double alpha_value,
                                 QString constrained_time_path_file, QString constrained_variable, double constrained_epsilon,
                                 QWidget *parent) : QWidget(parent)
{
    // Auxiliary : Horizontal line
    mpHorizontalLine = new QFrame;
    mpHorizontalLine->setFrameShape(QFrame::HLine);
    mpHorizontalLine->setFrameShadow(QFrame::Sunken);

    // Variables
    mpVariablesLabel = new QLabel(tr("Variable to optimize (t_final):"), this);
    mpVariablesComboBox = new QComboBox(this);
    foreach(QString var_name, variables) {
        mpVariablesComboBox->addItem(var_name);
    }
    int target_var_index = mpVariablesComboBox->findText(target_var);
    mpVariablesComboBox->setCurrentIndex(target_var_index);

    // Constrained variables
    mpConstrainedVariablesLabel = new QLabel(tr("Constrained variable:"), this);
    mpConstrainedVariablesComboBox = new QComboBox(this);
    foreach(QString var_name, variables) {
        mpConstrainedVariablesComboBox->addItem(var_name);
    }
    int target_var_index_constrained = mpConstrainedVariablesComboBox->findText(constrained_variable);
    mpConstrainedVariablesComboBox->setCurrentIndex(target_var_index_constrained);

    // Goal
    mpGoalButtonGroup = new QButtonGroup(this); // Has to have "this" as parent because it's never assigned to anything
    mpMinRadio = new QRadioButton(tr("Minimize"));
    mpMaxRadio = new QRadioButton(tr("Maximize"));
    toggleOptimType(maximize);
    mpGoalButtonGroup->addButton(mpMinRadio, mMinimizeButtonId);
    mpGoalButtonGroup->addButton(mpMaxRadio, mMaximizeButtonId);

    // Epsilon
    mpEpsilonLabel = new QLabel(tr("Accepted numerical error (ε)"));
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
    std::vector<QString> optimizers = {"CURVIF", "CURVIFGR"};
    optimizers.erase(std::remove(optimizers.begin(), optimizers.end(), optimizer_name), optimizers.end());
    mpOptimizerNameComboBox->addItem(optimizer_name);
    for (QString opt : optimizers) {
        mpOptimizerNameComboBox->addItem(opt);
    }
    pMainLayout->addWidget(mpOptimizerNameLabel);
    pMainLayout->addWidget(mpOptimizerNameComboBox);

    // Objective function
    mpObjectiveFunctionNameLabel = new QLabel(tr("Objective function name"));
    mpObjectiveFunctionNameComboBox = new QComboBox(this);
    std::vector<QString> functions = {"Alpha weighted path constrained", "Single variable"};
    functions.erase(std::remove(functions.begin(), functions.end(), objective_function_name), functions.end());
    mpObjectiveFunctionNameComboBox->addItem(objective_function_name);
    for (QString func : functions) {
        mpObjectiveFunctionNameComboBox->addItem(func);
    }
    pMainLayout->addWidget(mpObjectiveFunctionNameLabel);
    pMainLayout->addWidget(mpObjectiveFunctionNameComboBox);

    // Variable to optimize
    //mpSingleVariableOptimizationLabel = new QLabel(tr("Single variable optimization: set objective variable name"));
    //pMainLayout->addWidget(mpSingleVariableOptimizationLabel);

    // Grid general parameters
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

    // Alpha weighted optimization
    // TODO: read optional objective functions from somewhere (config file?)
    QFrame *hline1 = new QFrame; hline1->setFrameShape(QFrame::HLine); hline1->setFrameShadow(QFrame::Sunken);
    pMainLayout->addWidget(hline1);

    mpAlphaLabel = new QLabel(tr("Alpha weighted optimization: set alpha value (α)"));
    mpAlphaValue = new QDoubleSpinBox;
    //mpAlphaValue->setRange(0, 1);
    mpAlphaValue->setRange(0.0, 1.0);
    mpAlphaValue->setValue(alpha_value);
    mpAlphaValue->setSingleStep(0.0001);
    pMainLayout->addWidget(mpAlphaLabel);
    pMainLayout->addWidget(mpAlphaValue);

    // Grid constrained parameters
    QGridLayout *gridLayoutConstrained = new QGridLayout;
    gridLayoutConstrained->addWidget(mpConstrainedVariablesLabel   ,0,0);
    gridLayoutConstrained->addWidget(mpConstrainedVariablesComboBox,0,1);
    mpEpsilonConstrainedLabel = new QLabel(tr("Required closeness to constrained path"));
    mpEpsilonConstrainedComboBox = new SciNotationDoubleSpinbox;
    mpEpsilonConstrainedComboBox->setRange(0.0, 100.0);
    mpEpsilonConstrainedComboBox->setValue(constrained_epsilon);
    mpEpsilonConstrainedComboBox->setSingleStep(0.01);
    gridLayoutConstrained->addWidget(mpEpsilonConstrainedLabel   ,1,0);
    gridLayoutConstrained->addWidget(mpEpsilonConstrainedComboBox,1,1);
    pMainLayout->addLayout(gridLayoutConstrained);

    // Directory of path constrained condition
    mpConstrainedPathLabel = new QLabel(tr("Constraints (*.csv file)"));
    pMainLayout->addWidget(mpConstrainedPathLabel);
    QString defaultLimitedPathFolderPath = constrained_time_path_file;
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
double OptimizationTab::getConstrainedEpsilon() const
{
    return mpEpsilonConstrainedComboBox->value();
}
QString OptimizationTab::getTargetVariable() const
{
    return mpVariablesComboBox->currentText();
}
QString OptimizationTab::getConstrainedVariable() const
{
    return mpConstrainedVariablesComboBox->currentText();
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
