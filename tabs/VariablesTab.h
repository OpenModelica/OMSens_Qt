#ifndef VARIABLESTAB_H
#define VARIABLESTAB_H

#include <QWidget>
#include <QTableWidget>

class VariablesTab : public QWidget
{
    Q_OBJECT
public:
    explicit VariablesTab(QList<QString> variables, QWidget *parent = 0);
    // Getters
    QTableWidget *getVariablesTable() const;
    // Conventions:
    //   Columns ordering
    static const int varColPos  = 0;
    static const int cboxColPos = 1;

private:
    QTableWidget *mpVariablesTable;
signals:

public slots:
};

#endif // VARIABLESTAB_H
