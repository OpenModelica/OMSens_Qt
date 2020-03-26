#ifndef PLOTSWEEPTAB_H
#define PLOTSWEEPTAB_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>

class PlotSweepTab : public QWidget
{
    Q_OBJECT
public:
    explicit PlotSweepTab(bool plot_upper_lower_limit,
                          QWidget *parent = nullptr);


private:
    QCheckBox *mpUpperLowerLimitCheckBox;
    bool getUpperLowerLimitCheckbox() const;
signals:

public slots:
};

#endif // PLOTSWEEPTAB_H
