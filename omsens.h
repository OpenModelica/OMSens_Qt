#ifndef OMSENS_H
#define OMSENS_H

#include <QMainWindow>

namespace Ui {
class OMSens;
}

class OMSens : public QMainWindow
{
    Q_OBJECT

public:
    explicit OMSens(QVector<QString> modelVars,QWidget *pParent);
    ~OMSens();

private slots:
    void on_actionEmpirical_Indices_triggered();

    void on_actionCURVI_Sens_triggered();

private:
    Ui::OMSens *ui;
    // Model info for testing
    QVector<QString> modelVars;
};

#endif // OMSENS_H
