#ifndef LINESPLOTVISUALIZER_H
#define LINESPLOTVISUALIZER_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QLineEdit>
#include "../BaseResultsDialog.h"

class LinesPlotVisualizer: public QDialog
{
    Q_OBJECT
public:
    LinesPlotVisualizer(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *parent = nullptr);

private:
    QString executablePath;
    QString librariesPath;
    QString resultsPath;
};

#endif // LINESPLOTVISUALIZER_H
