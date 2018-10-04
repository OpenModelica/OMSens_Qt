#ifndef PARAMETERSTAB_H
#define PARAMETERSTAB_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QDoubleSpinBox>


class ParametersSimpleTab : public QWidget
{
    Q_OBJECT
public:
    explicit ParametersSimpleTab(QList<QString> parameters, double percentage, QWidget *parent = 0);
    // Getters
    QTableWidget *getParametersTable() const;
    double  getPercentageValue() const;
    // Conventions:
    //   Columns ordering
    int paramColPos = 0;
    int cboxColPos  = 1;


private:
    // Description
    QLabel             *mpBriefDescriptionLabel;
    // Table
    QTableWidget *mpParametersTable;
    // Percentage
    QLabel *mpPercentageLabel;
    QDoubleSpinBox *mpPercentageBox;

signals:

public slots:
};

#endif // PARAMETERSTAB_H
