#ifndef OPTIMIZATIONTAB_H
#define OPTIMIZATIONTAB_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QDoubleSpinBox>

class OptimizationTab : public QWidget
{
    Q_OBJECT
public:
    explicit OptimizationTab(QList<QString> variables, QWidget *parent = nullptr);

    // Conventions
    //   Columns ordering
    int mMinimizeButtonId = 0;
    int mMaximizeButtonId = 1;
    double getEpsilon() const;
    QString getTargetVariable() const;
    int getGoalId() const;

private:
    // Variable
    QLabel    *mpVariablesLabel;
    QComboBox *mpVariablesComboBox;
    QButtonGroup *mpGoalButtonGroup;
    QRadioButton *mpMinRadio;
    QRadioButton *mpMaxRadio;
    // Epsilon
    QLabel         *mpEpsilonLabel;
    QDoubleSpinBox *mpEpsilonBox;

signals:

public slots:
};

#endif // OPTIMIZATIONTAB_H
