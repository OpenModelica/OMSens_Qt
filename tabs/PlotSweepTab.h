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

    bool getUpperLowerLimitCheckbox() const;
private:
    QCheckBox *mpUpperLowerLimitCheckBox;
signals:

public slots:
};

#endif // PLOTSWEEPTAB_H
