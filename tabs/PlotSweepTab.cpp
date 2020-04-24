#include "PlotSweepTab.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>

PlotSweepTab::PlotSweepTab(bool plot_upper_lower_limit,
                           QWidget *parent) : QWidget(parent)
{
    QLabel *mpUpperLowerLimitLabel = new QLabel(tr("Plot upper and lower limit: "));
    // Set checkbox
    mpUpperLowerLimitCheckBox = new QCheckBox;
    mpUpperLowerLimitCheckBox->setChecked(plot_upper_lower_limit);

    QGridLayout *gridLayout = new QGridLayout;
    // Variables
    gridLayout->addWidget(mpUpperLowerLimitLabel   ,1,0);
    gridLayout->addWidget(mpUpperLowerLimitCheckBox,1,1);

    QVBoxLayout *pMainLayout = new QVBoxLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    pMainLayout->addLayout(gridLayout);

    // Layout settings
    setLayout(pMainLayout);
}

bool PlotSweepTab::getUpperLowerLimitCheckbox() const
{
    return mpUpperLowerLimitCheckBox->isChecked();
}
