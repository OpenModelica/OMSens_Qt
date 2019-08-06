#ifndef HISTOGRAMCREATOR_H
#define HISTOGRAMCREATOR_H

#include <QDialog>
#include <QLabel>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QLineEdit>
#include "../BaseResultsDialog.h"

class HistogramCreator : public QDialog
{
    Q_OBJECT
public:
    HistogramCreator(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *parent = nullptr);

    QString progressDialogTextForCurrentTime();
    void showHistogramVariable();
    void showHistogramParameter();

private:
    QString executablePath;
    QString librariesPath;
    QString resultsPath;

    QComboBox *options_variables_box;
    QComboBox *options_variables_box_2;
    QComboBox *options_parameters_box;
    QLineEdit *options_time_box;

    int makePNG(QString args);

    QTabWidget *mpTabWidget;
    QDialogButtonBox   *mpButtonBox;
};

#endif // HISTOGRAMCREATOR_H
