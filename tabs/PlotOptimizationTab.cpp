#include "PlotOptimizationTab.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QtMath>
#include <QFileDialog>
#include <vector>
#include <algorithm>
#include <string>
#include <QCheckBox>
#include <QLabel>

PlotOptimizationTab::PlotOptimizationTab(bool plot_restriction, bool plot_std_run,
                                         QWidget *parent) : QWidget(parent)
{
    QLabel *mpPlotRestrictionLabel = new QLabel(tr("Plot Restriction"));
    QLabel *mpPlotStandardRunLabel = new QLabel(tr("Plot Std Run"));
    // Set checkbox
    mpRestrictionsCheckBox = new QCheckBox;
    mpRestrictionsCheckBox->setChecked(plot_restriction);
    mpStandardRunCheckBox = new QCheckBox;
    mpStandardRunCheckBox->setChecked(plot_std_run);

    QGridLayout *gridLayout = new QGridLayout;
    // Variables
    gridLayout->addWidget(mpPlotRestrictionLabel   ,0,0);
    gridLayout->addWidget(mpRestrictionsCheckBox,0,1);
    gridLayout->addWidget(mpPlotStandardRunLabel   ,1,0);
    gridLayout->addWidget(mpStandardRunCheckBox,1,1);

    QVBoxLayout *pMainLayout = new QVBoxLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    pMainLayout->addLayout(gridLayout);

    // Layout settings
    setLayout(pMainLayout);
}

// Getters
bool PlotOptimizationTab::getRestrictionCheckbox() const
{
    return mpRestrictionsCheckBox->isChecked();
}
bool PlotOptimizationTab::getStandardRunCheckbox() const
{
    return mpStandardRunCheckBox->isChecked();
}
