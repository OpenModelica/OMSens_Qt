#ifndef PARAMETERSEXTENDEDTAB_H
#define PARAMETERSEXTENDEDTAB_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>

class ParametersExtendedTab : public QWidget
{
    Q_OBJECT
public:
    explicit ParametersExtendedTab(QList<QString> parameters, QWidget *parent = 0);
    // Getters
    QTableWidget *getParametersTable() const;
    // Conventions:
    //   Columns ordering
    int paramColPos    = 0;
    int nItersColPos   = 1;
    int pertPercColPos = 2;
    int cboxColPos     = 3;

private:
    // Description
    QLabel *mpBriefDescriptionLabel;
    // Table
    QTableWidget *mpParametersTable;

signals:

public slots:
};

#endif // PARAMETERSEXTENDEDTAB_H
