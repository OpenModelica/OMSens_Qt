#include "tabs/PlotsTab.h"

PlotsTab::PlotsTab(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *parent) : QDialog(parent)
{
    setMinimumWidth(410);
    setWindowTitle("Plots Tab");
}
