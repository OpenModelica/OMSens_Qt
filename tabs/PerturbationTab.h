#ifndef PERTURBATIONTAB_H
#define PERTURBATIONTAB_H

#include <QTabWidget>
#include <QLabel>
#include "../ForceSignDoubleSpinbox.h"


class PerturbationTab : public QTabWidget
{
    Q_OBJECT
public:
    explicit PerturbationTab(double percentage, QWidget *parent = nullptr);
    double getPerturbationValue() const;

private:
    // Perturbation
    QLabel         *mpPerturbationLabel;
    ForceSignDoubleSpinbox *mpPerturbationBox;

signals:

public slots:
};

#endif // PERTURBATIONTAB_H
