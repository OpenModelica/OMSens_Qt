#ifndef BASERESULTSDIALOG_H
#define BASERESULTSDIALOG_H

#include <QDialog>

class BaseResultsDialog : public QDialog
{
    Q_OBJECT
public:
    BaseResultsDialog(QWidget *parent = nullptr) : QDialog(parent) {}

signals:

public slots:
};

#endif // BASERESULTSDIALOG_H
