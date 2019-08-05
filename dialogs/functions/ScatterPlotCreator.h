#ifndef SCATTERPLOTCREATOR_H
#define SCATTERPLOTCREATOR_H

#include <QDialog>
#include <QLabel>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QComboBox>

class ScatterPlotCreator: public QWidget
{
public:
    ScatterPlotCreator(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *parent = nullptr);
    QString progressDialogTextForCurrentTime();
    void showScatterPlot();

private:
    QString executablePath;
    QString librariesPath;
    QString resultsPath;

    QComboBox *options_parameters_box;
    QComboBox *options_time_box;

    int makePNG(QString png_filename);

    QTabWidget *mpTabWidget;
    QDialogButtonBox   *mpButtonBox;
};

#endif // SCATTERPLOTCREATOR_H
