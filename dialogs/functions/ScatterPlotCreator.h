#ifndef SCATTERPLOTCREATOR_H
#define SCATTERPLOTCREATOR_H

#include <QDialog>
#include <QLabel>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>

class ScatterPlotCreator: public QWidget
{
public:
    ScatterPlotCreator(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *parent = nullptr);
    QString progressDialogTextForCurrentTime();
    void showScatterPlotVariables();
    void showScatterPlotParameters();

private:
    QString executablePath;
    QString librariesPath;
    QString resultsPath;

//    QComboBox *options_time_box;
    QLineEdit *options_time_box;

    QComboBox *options_variables_box;

    QComboBox *options_parameters_box;
    QComboBox *options_variables_box_2;

    int makePNG(QString args);

    QTabWidget *mpTabWidget;
    QDialogButtonBox   *mpButtonBox;
};

#endif // SCATTERPLOTCREATOR_H
