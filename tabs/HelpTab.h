#ifndef HELPTAB_H
#define HELPTAB_H

#include <QWidget>
#include <QLabel>

class HelpTab : public QWidget
{
    Q_OBJECT
public:
    explicit HelpTab(QString description, QWidget *parent = nullptr);
private:
    QLabel *mDescription;

signals:

public slots:
};

#endif // HELPTAB_H
