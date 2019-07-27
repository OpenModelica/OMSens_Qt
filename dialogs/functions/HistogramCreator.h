#ifndef HISTOGRAMCREATOR_H
#define HISTOGRAMCREATOR_H

#include <QDialog>
#include <QLabel>
#include <QTabWidget>
#include <QDialogButtonBox>
#include "../BaseResultsDialog.h"

class HistogramCreator : public QDialog
{
    Q_OBJECT
public:
    HistogramCreator(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *parent = nullptr);

    QString progressDialogTextForCurrentTime();
    void showHistogram();

private:
    QString executablePath;
    QString librariesPath;
    QString resultsPath;

    int makePNG(QString png_filename);

    QTabWidget *mpTabWidget;
    QDialogButtonBox   *mpButtonBox;
};

#endif // HISTOGRAMCREATOR_H
