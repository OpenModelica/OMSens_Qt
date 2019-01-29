#ifndef VARIABLESTAB_H
#define VARIABLESTAB_H

#include <QWidget>
#include <QTableWidget>

// Aux Structs
struct VariableInclusion{
  QString name;
  bool include;

  VariableInclusion(QString name, bool include): name(name), include(include){}
};

// Class
class VariablesTab : public QWidget
{
    Q_OBJECT
public:
    // Constructors
    explicit VariablesTab(QList<VariableInclusion> vars_inclusion, QWidget *parent = 0);
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
