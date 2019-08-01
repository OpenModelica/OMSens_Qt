#include "dialogs/PlotsDialog.h"

PlotsDialog::PlotsDialog(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *parent) : QDialog(parent)
{
    setMinimumWidth(410);
    setWindowTitle("Plots Tab");
}
