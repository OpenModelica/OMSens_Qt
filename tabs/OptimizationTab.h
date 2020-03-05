#ifndef OPTIMIZATIONTAB_H
#define OPTIMIZATIONTAB_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include "../SciNotationDoubleSpinbox.h"

class OptimizationTab : public QWidget
{
    Q_OBJECT
public:
    explicit OptimizationTab(QList<QString> variables, QString target_var, double epsilon, double percentage, bool maximize, QWidget *parent = nullptr);

    // Conventions
    // Columns ordering
    int mMinimizeButtonId = 0;
    int mMaximizeButtonId = 1;

    // Getters
    double getEpsilon() const;
    QString getTargetVariable() const;
    int getGoalId() const;
    double  getBoundariesValue() const;

    QString getOptimizerName() const;
    QString getObjectiveFunctionName() const;
    double getAlphaValue() const;
    QString getConstrainedTimePathFile() const;

private:
    // Variable
    QLabel    *mpVariablesLabel;
    QComboBox *mpVariablesComboBox;
    QButtonGroup *mpGoalButtonGroup;
    QRadioButton *mpMinRadio;
    QRadioButton *mpMaxRadio;

    // Optimizer
    QFrame *mpHorizontalLine;
    QLabel *mpOptimizerNameLabel;
    QComboBox *mpOptimizerNameComboBox;
    QLabel *mpLimitedPathFolderLabel;
    QLabel *mpLimitedPathFolderValue;
    QPushButton *mpChooseCSVFileButton;

    QLabel *mpObjectiveFunctionNameLabel;
    QComboBox *mpObjectiveFunctionNameComboBox;

    QLabel *mpAlphaLabel;
    QDoubleSpinBox *mpAlphaValue;

    QLabel *mpSingleVariableOptimizationLabel;
    QLabel *mpConstrainedPathLabel;

    // Epsilon
    QLabel   *mpEpsilonLabel;
    SciNotationDoubleSpinbox *mpEpsilonBox;
    QLabel   *mpEpsilonHintLabel;

    // Boundaries
    QLabel *mpBoundariesLabel;
    QDoubleSpinBox *mpBoundariesBox;

    void toggleOptimType(bool maximize);

signals:

public slots:

private slots:
    void launchChooseCSVFileDialog();
};

#endif // OPTIMIZATIONTAB_H
