#ifndef OMSENS_H
#define OMSENS_H

#include <QMainWindow>
#include "model.h"

namespace Ui {
class OMSens;
}

class OMSens : public QMainWindow
{
    Q_OBJECT

public:
    explicit OMSens(Model model,QWidget *pParent=0);
    ~OMSens();

private slots:
    void on_actionEmpirical_Indices_triggered();

    void on_actionCURVI_Sens_triggered();

    void on_actionMultiparam_Sweep_triggered();

private:
    Ui::OMSens *ui;
    // Model info for testing
    Model model;
};

#endif // OMSENS_H
