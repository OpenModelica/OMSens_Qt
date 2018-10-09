#ifndef OPTIMIZATIONRESULTOTHERTAB_H
#define OPTIMIZATIONRESULTOTHERTAB_H

#include <QTableView>
#include <QTabWidget>
#include <QString>
#include <QJsonDocument>

class OptimizationResultOtherTab : public QTabWidget
{
    Q_OBJECT
public:
    OptimizationResultOtherTab(QJsonDocument vectorialResults, QWidget *pParent = nullptr);

private:
    // GUI members
    QTableView *mpFxTable;
    // Data members
    double m_f_x_opt;
    double m_f_x0;
    double mStopTime;
    QString mVariable;

//    "f(x)_opt": 322.6798500000257,
//    "f(x0)": 339.663,
//    "stop_time": 3,
//    "variable": "outvar1",


signals:

public slots:
};

#endif // OPTIMIZATIONRESULTOTHERTAB_H
