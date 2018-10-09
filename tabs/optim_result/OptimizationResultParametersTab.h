#ifndef OPTIMIZATIONRESULTPARAMETERSTAB_H
#define OPTIMIZATIONRESULTPARAMETERSTAB_H

#include <QTabWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTableView>

class OptimizationResultParametersTab : public QTabWidget
{
    Q_OBJECT
public:
    OptimizationResultParametersTab(QJsonDocument vectorialResults, QWidget *pParent= 0);

private:
    // GUI members
    QTableView *mpXTable;
    // Data members
    QJsonObject m_x_opt;
    QJsonObject m_x0;

signals:

public slots:
};

#endif // OPTIMIZATIONRESULTPARAMETERSTAB_H
