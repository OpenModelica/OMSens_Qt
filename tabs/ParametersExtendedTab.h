#ifndef PARAMETERSEXTENDEDTAB_H
#define PARAMETERSEXTENDEDTAB_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>

// Aux structs
struct PerturbationRow{
   QString name;
   int perturbation_type_id;
   int iterations;
   double percentage;
   double fixed_value;
   bool operator< (PerturbationRow& b) {return (this->name < b.name);}
};

// Class
class ParametersExtendedTab : public QWidget
{
    Q_OBJECT
public:
    explicit ParametersExtendedTab(QList<PerturbationRow> pert_rows, QWidget *parent = 0);
    // Getters
    QTableWidget *getParametersTable() const;
    // Conventions:
    //   Columns ordering
    int nameColPos       = 0;
    int pertTypeColPos   = 1;
    int nItersColPos     = 2;
    int pertRangeColPos  = 3;
    int fixedValueColPos = 4;
    // Perturbation types (we use these instead of enums because QVariants don't like enums)
    static const int NoPerturbationId    = 0;
    static const int SweepPerturbationId = 1;
    static const int FixedPerturbationId = 2;


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
    void pertTypeChanged(int);

signals:

public slots:
};

#endif // PARAMETERSEXTENDEDTAB_H
