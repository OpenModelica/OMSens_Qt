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
    QPushButton *mpAddRowButton;
    // Conventions:
    //   Columns ordering
    static const int paramsColNum = 0;
    static const int numberOfIterationsColNum = 1;
    static const int perturbationColNum = 2;
    static const int removeRowButtonColNum = 3;
    // Forms min, max, default values
    static const double defaultTime= 2000;
    static const double maxTargetTime= 5000;
    static const int maxNumberOfIterations= 50000;
    static const double minPerturbationPercentage= -100;
    static const double maxPerturbationPercentage= 100;

    // Auxs:
    void initializeWindowSettings();
    void setHeading();
    void initializeButton();
    void initializeFormInputsAndLabels();
    void initializeVarsToPlotForms();
    void initializeParamsToSweepForms();
    void initializeStopTimeForms();
    void initializeParamsToSweepLabel();
    void setParamsTableHeaders();
    void setParamsTableSettings();
    void addExampleRowToParamsTable();
    void resizeParamsTable();
    void addParamsComboBoxToTable(const int rowNum);
    void addIterationsSpinBoxToTable(const int rowNum);
    void addPerturbSpinBoxToTable(const int rowNum);
    void addWidgetsToLayout(QGridLayout *pMainLayout);

    void addRemoveButtonToTable(const int rowNum);

private slots:
    void runMultiParamSweep();
    void removeRowSlot();
    void addNewRowToParamsSweepTable();
};

#endif // MULTIPARAMSWEEPDIALOG_H
