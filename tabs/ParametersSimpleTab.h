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
    explicit ParametersSimpleTab(QList<QString> parameters, QString quickExplanation, QWidget *parent = 0);
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
