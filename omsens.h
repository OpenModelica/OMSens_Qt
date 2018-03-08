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

    void on_actionRun_Script_triggered();

    void on_actionOpen_Sens_Analysis_Result_triggered();

    void on_actionRun_Curvi_Sens_Script_triggered();
    void on_actionOpen_Sens_Analysis_Image_triggered();

private:
    Ui::OMSens *ui;
    // Model info for testing
    Model model;
};

#endif // OMSENS_H
