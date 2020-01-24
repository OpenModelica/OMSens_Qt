#ifndef BASERUNSPECSDIALOG_H
#define BASERUNSPECSDIALOG_H

#include <QDialog>

class BaseRunSpecsDialog : public QDialog
{
    Q_OBJECT
public:
    BaseRunSpecsDialog(QWidget *parent = 0) : QDialog(parent) {}

    // Getters
    virtual QJsonDocument getRunSpecifications() const = 0;
    virtual QString getDestFolderPath() const = 0;

    // Convention
    virtual QString pythonScriptName() = 0;

signals:

public slots:
};

#endif // BASERUNSPECSDIALOG_H
