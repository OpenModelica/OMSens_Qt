#ifndef PARAMETERSTAB_H
#define PARAMETERSTAB_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QDoubleSpinBox>


// Aux Structs
struct ParameterInclusion{
  QString name;
  bool include;

  ParameterInclusion(QString name, bool include): name(name), include(include){}
};

// Class
class ParametersSimpleTab : public QWidget
{
    Q_OBJECT
public:
    explicit ParametersSimpleTab(QList<ParameterInclusion> params_inclusion, QString quickExplanation, QWidget *parent = 0);
    // Getters
    QTableWidget *getParametersTable() const;
    // Conventions:
    //   Columns ordering
    int paramColPos = 0;
    int cboxColPos  = 1;


private:
    // Description
    QLabel             *mpBriefDescriptionLabel;
    // Table
    QTableWidget *mpParametersTable;

signals:

public slots:
};

#endif // PARAMETERSTAB_H
