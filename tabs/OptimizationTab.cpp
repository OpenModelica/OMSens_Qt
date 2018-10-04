#include "OptimizationTab.h"

#include <QGridLayout>

OptimizationTab::OptimizationTab(QList<QString> variables, QWidget *parent) : QWidget(parent)
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
    mpEpsilonBox   = new QDoubleSpinBox;
    mpEpsilonBox->setRange(0,0.9);
    mpEpsilonBox->setValue(0.1);
    mpEpsilonBox->setSingleStep(0.001);
    mpEpsilonBox->setDecimals(12);

    // Layout
    QGridLayout *pMainLayout = new QGridLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    // Variables
    pMainLayout->addWidget(mpVariablesLabel   ,0,0);
    pMainLayout->addWidget(mpVariablesComboBox,0,1);
    pMainLayout->addWidget(mpMinRadio         ,0,2);
    pMainLayout->addWidget(mpMaxRadio         ,0,3);
    // Epsilon
    pMainLayout->addWidget(mpEpsilonLabel,2,0);
    pMainLayout->addWidget(mpEpsilonBox  ,2,1);
    // Layout settings
    setLayout(pMainLayout);
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
