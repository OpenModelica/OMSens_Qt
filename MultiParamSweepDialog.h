#ifndef MULTIPARAMSWEEPDIALOG_H
#define MULTIPARAMSWEEPDIALOG_H

#include "DualLists.h"
#include "model.h"

#include <QDialog>
#include <QDoubleSpinBox>
#include <QFrame>
#include <QGridLayout>
#include <QTableWidget>


class Label;
class MultiParamSweepDialog : public QDialog
{
    Q_OBJECT
public:
    MultiParamSweepDialog(Model model, QWidget *pParent = 0);
    QGridLayout * initializeLayout();


private:
    // Model information members
    Model model;
    // GUI members
    QPushButton *mpRunButton;
    Label *mpHeading;
    QFrame *mpHorizontalLine;
    Label *mpVarsToPlotLabel;
    DualLists *mpVarsToPlotDualLists;
    Label *mpStopTimeLabel;
    QDoubleSpinBox *mpStopTimeBox;
    Label *mpParamsToSweepLabel;
    QTableWidget *mpParamsToSweepTable;
    // Auxs:
    void initializeWindowSettings();
    void setHeading();

    void initializeButton();

    void initializeFormInputsAndLabels(const double defaultTime, const double maxTargetTime, Model model, const int perturbationColNum, const double minPerturbationPercentage, const double maxPerturbationPercentage, const int paramsColNum, const int numberOfIterationsColNum, const int maxNumberOfIterations);

    void initializeVarsToPlotForms(Model model);

    void initializeParamsToSweepForms(Model model, const int perturbationColNum, const double minPerturbationPercentage, const double maxPerturbationPercentage, const int paramsColNum, const int numberOfIterationsColNum, const int maxNumberOfIterations);

    void initializeStopTimeForms(const double maxTargetTime, const double defaultTime);

    void initializeParamsToSweepLabel();

    void setParamsTableHeaders();

    void setParamsTableSettings();

    void addExampleRowToParamsTable(Model model, const int perturbationColNum, const double minPerturbationPercentage, const double maxPerturbationPercentage, const int paramsColNum, const int numberOfIterationsColNum, const int maxNumberOfIterations);

    void resizeParamsTable();

    void addParamsComboBoxToTable(const int rowNum, const int paramsColNum, Model model);

    void addIterationsSpinBoxToTable(const int rowNum, const int numberOfIterationsColNum, const int maxNumberOfIterations);

    void addPerturbSpinBoxToTable(const double minPerturbationPercentage, const double maxPerturbationPercentage, const int rowNum, const int perturbationColNum);
    void addWidgetsToLayout(QGridLayout *pMainLayout);

private slots:
    void runMultiParamSweep();
};

#endif // MULTIPARAMSWEEPDIALOG_H
