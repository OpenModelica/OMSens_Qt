#include "OptimizationTab.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QtMath>

OptimizationTab::OptimizationTab(QList<QString> variables, double percentage, QWidget *parent) : QWidget(parent)
{
    // Variables
    mpVariablesLabel = new QLabel(tr("Variable:"), this);
    mpVariablesComboBox = new QComboBox(this);
    foreach(QString var_name, variables) {
        mpVariablesComboBox->addItem(var_name);
    }
    // Goal
    mpGoalButtonGroup = new QButtonGroup(this); // Has to have "this" as parent because it's never assigned to anything
    mpMinRadio = new QRadioButton(tr("Minimize"));
    mpMinRadio->toggle(); //This index start selected by default
    mpMaxRadio = new QRadioButton(tr("Maximize"));
    mpGoalButtonGroup->addButton(mpMinRadio, mMinimizeButtonId);
    mpGoalButtonGroup->addButton(mpMaxRadio, mMaximizeButtonId);
    // Epsilon
    mpEpsilonLabel = new QLabel(tr("Epsilon"));
    mpEpsilonBox = new SciNotationDoubleSpinbox;
    mpEpsilonBox->setRange(std::numeric_limits<double>::min(), 1-std::numeric_limits<double>::min());
    mpEpsilonBox->setValue(0.1);
    mpEpsilonBox->setSingleStep(0.01);
    // Boundaries
    mpBoundariesLabel = new QLabel(tr("Perturbation boundaries:"));
    mpBoundariesBox = new QDoubleSpinBox;
    mpBoundariesBox->setRange(0.01, std::numeric_limits<double>::max());
    mpBoundariesBox->setValue(percentage);
    mpBoundariesBox->setPrefix("±");
    mpBoundariesBox->setSuffix("%");

    // Layout
    QGridLayout *pMainLayout = new QGridLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    // Variables
    pMainLayout->addWidget(mpVariablesLabel   ,0,0);
    pMainLayout->addWidget(mpVariablesComboBox,0,1);
    pMainLayout->addWidget(mpMinRadio         ,0,2);
    pMainLayout->addWidget(mpMaxRadio         ,0,3);
    // Epsilon
    pMainLayout->addWidget(mpEpsilonLabel  ,2,0);
    pMainLayout->addWidget(mpEpsilonBox    ,2,1);
    // Boundaries
    pMainLayout->addWidget(mpBoundariesLabel,3,0);
    pMainLayout->addWidget(mpBoundariesBox  ,3,1);

    // Layout settings
    setLayout(pMainLayout);
}


// Getters
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
