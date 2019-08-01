#ifndef PLOTSTAB_H
#define PLOTSTAB_H

#include <QObject>
#include <QDialog>
#include <QWidget>

class PlotsTab : public QDialog
{
    Q_OBJECT
public:
    PlotsTab(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *parent = nullptr);
};

#endif // PLOTSTAB_H
