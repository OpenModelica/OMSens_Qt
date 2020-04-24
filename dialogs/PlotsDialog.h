#ifndef PLOTSDIALOG_H
#define PLOTSDIALOG_H

#include <QObject>
#include <QDialog>
#include <QWidget>

class PlotsDialog : public QDialog
{
    Q_OBJECT
public:
    PlotsDialog(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *parent = nullptr);
};

#endif // PLOTSDIALOG_H
