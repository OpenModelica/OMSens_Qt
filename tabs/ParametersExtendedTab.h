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
    int paramColPos      = 0;
    int pertTypeColPos   = 1;
    int nItersColPos     = 2;
    int pertRangeColPos  = 3;
    int fixedValueColPos = 4;
    // Perturbation types
    int NoPerturbationId    = 0;
    int SweepPerturbationId = 1;
    int FixedPerturbationId = 2;


private:
    // Description
    QLabel *mpBriefDescriptionLabel;
    // Table
    QTableWidget *mpParametersTable;
    // Auxs
    void enableOrDisableCellsOnRow(int rowNum);
    void disablePertRangeCellInRow(int rowNum);
    void disableFixedValueCellInRow(int rowNum);
    void disableNumberOfItersCellInRow(int rowNum);
    void enableAllCells(int rowNum);

private slots:
    void pertTypeChanged(int ignoreMe);

signals:

public slots:
};

#endif // PARAMETERSEXTENDEDTAB_H
