#ifndef PLOTOPTIMIZATIONTAB_H
#define PLOTOPTIMIZATIONTAB_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>

class PlotOptimizationTab : public QWidget
{
    Q_OBJECT

public:
    explicit PlotOptimizationTab(bool plot_restriction, bool plot_std_run,
                                 QWidget *parent = nullptr);
    bool getRestrictionCheckbox() const;
    bool getStandardRunCheckbox() const;
private:
    QCheckBox *mpRestrictionsCheckBox;
    QCheckBox *mpStandardRunCheckBox;
};

#endif // PLOTOPTIMIZATIONTAB_H
