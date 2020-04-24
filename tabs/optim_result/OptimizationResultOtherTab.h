#ifndef OPTIMIZATIONRESULTOTHERTAB_H
#define OPTIMIZATIONRESULTOTHERTAB_H

#include <QLabel>
#include <QTableView>
#include <QTabWidget>
#include <QString>
#include <QPushButton>
#include <QJsonDocument>

class OptimizationResultOtherTab : public QTabWidget
{
    Q_OBJECT
public:
    OptimizationResultOtherTab(QJsonDocument vectorialResults, QWidget *pParent = nullptr);

private:
    // GUI members
    // f(x)
    QTableView *mpFxTable;
    // Data members
    QString mVariable;
    double m_f_x_opt;
    double m_f_x0;
};

#endif // OPTIMIZATIONRESULTOTHERTAB_H
