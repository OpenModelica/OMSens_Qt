#ifndef HISTOGRAMCREATOR_H
#define HISTOGRAMCREATOR_H

#include <QDialog>
#include <QLabel>
#include <QTabWidget>
#include <QDialogButtonBox>
#include "../BaseResultsDialog.h"

class HistogramCreator : public QDialog
{
    Q_OBJECT
public:
    HistogramCreator(QWidget *parent = nullptr);

    QString progressDialogTextForCurrentTime();
    int makeHistogram();

private:
    QTabWidget *mpTabWidget;
    QDialogButtonBox   *mpButtonBox;
};

#endif // HISTOGRAMCREATOR_H
