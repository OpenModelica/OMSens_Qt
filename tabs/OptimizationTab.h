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
    explicit OptimizationTab(QList<QString> variables, QString target_var, double epsilon, double percentage, bool maximize,
                             QString optimizer_name, QString objective_function_name, double alpha_value,
                             QString constrained_time_path_file, QString constrained_variable, double constrained_epsilon,
                             QWidget *parent = nullptr);

    // Conventions
    // Columns ordering
    int mMinimizeButtonId = 0;
    int mMaximizeButtonId = 1;

    // Getters
    double getEpsilon() const;
    double getConstrainedEpsilon() const;
    QString getTargetVariable() const;
    QString getConstrainedVariable() const;
    int getGoalId() const;
    double  getBoundariesValue() const;

    QString getOptimizerName() const;
    QString getObjectiveFunctionName() const;
    double getAlphaValue() const;
    QString getConstrainedTimePathFile() const;

private:
    // Variable
    QLabel    *mpVariablesLabel, *mpConstrainedVariablesLabel;
    QComboBox *mpVariablesComboBox, *mpConstrainedVariablesComboBox;
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
    QLabel   *mpEpsilonLabel, *mpEpsilonConstrainedLabel;
    SciNotationDoubleSpinbox *mpEpsilonBox, *mpEpsilonConstrainedComboBox;
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
