#ifndef INDIVSENSANALTYPEDIALOG_H
#define INDIVSENSANALTYPEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include "model.h"


class IndivSensAnalTypeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit IndivSensAnalTypeDialog(Model model, QWidget *parent = 0);
    // Members
    bool choseW3InsteadOfOpenModel;

private:
    // GUI
    QLabel      *mpChooseAnalysisLabel;
    QPushButton *mpRunW3SampleButton;
    QPushButton *mpRunOpenModelButton;

signals:


private slots:
    void chooseW3Sample();
    void chooseOpenModel();
};

#endif // INDIVSENSANALTYPEDIALOG_H
