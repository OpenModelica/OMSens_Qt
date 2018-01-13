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
    explicit OMSens(QWidget *parent = 0);
    ~OMSens();

private slots:
    void on_actionRel_Sens_triggered();

private:
    Ui::OMSens *ui;
};

#endif // OMSENS_H
