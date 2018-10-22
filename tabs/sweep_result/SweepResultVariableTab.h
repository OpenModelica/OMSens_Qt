#ifndef SWEEPRESULTVARIABLETAB_H
#define SWEEPRESULTVARIABLETAB_H

#include <QWidget>
#include <QJsonObject>
#include <QComboBox>
#include <QLabel>
#include <QDialog>

class SweepResultVariableTab : public QDialog
{
    Q_OBJECT
public:
    SweepResultVariableTab(QJsonObject mVarNameToPlotMap, QWidget *pParent = 0);

private:
    // GUI members
    QLabel      *mpVariablesLabel;
    QComboBox   *mpVariablesComboBox;
    QPushButton *mpOpenPlotButton;
    // Data members
    QJsonObject mVarNameToPlotMap;
    QList<QString> mVariables;

private slots:
    void openSelectedVarPlot();
};

#endif // SWEEPRESULTVARIABLETAB_H
