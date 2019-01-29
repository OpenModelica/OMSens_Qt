#ifndef VARIABLESTAB_H
#define VARIABLESTAB_H

#include <QWidget>
#include <QTableWidget>

// Aux Structs
struct VariableToInclude{
  QString name;
  bool include;

  VariableToInclude(QString name, bool include): name(name), include(include){}
};

// Class
class VariablesTab : public QWidget
{
    Q_OBJECT
public:
    explicit VariablesTab(QList<QString> variables, QWidget *parent = 0);
    explicit VariablesTab(QList<VariableToInclude> vars_to_include, QWidget *parent = 0);
    // Getters
    QTableWidget *getVariablesTable() const;
    // Conventions:
    //   Columns ordering
    static const int varColPos  = 0;
    static const int cboxColPos = 1;

private:
    QTableWidget *mpVariablesTable;
    void initialize(QList<VariableToInclude> vars_to_include);

signals:

public slots:
};

#endif // VARIABLESTAB_H
