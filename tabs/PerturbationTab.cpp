#include "PerturbationTab.h"

#include <QGridLayout>

PerturbationTab::PerturbationTab(double percentage, QWidget *parent) : QTabWidget(parent)
{
    // Perturbation
    mpPerturbationLabel = new QLabel(tr("Perturbation (choose + or -):"));
    mpPerturbationBox = new ForceSignDoubleSpinbox;
    mpPerturbationBox->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    mpPerturbationBox->setValue(percentage);
    mpPerturbationBox->setSuffix("%");

    // Layout
    QGridLayout *pMainLayout = new QGridLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    // Perturbation
    pMainLayout->addWidget(mpPerturbationLabel,0,0);
    pMainLayout->addWidget(mpPerturbationBox  ,0,1);

    // Layout settings
    setLayout(pMainLayout);

}

double PerturbationTab::getPerturbationValue() const
{
    return mpPerturbationBox->value();
}
