/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-2026, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF AGPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.8.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES
 * RECIPIENT'S ACCEPTANCE OF THE OSMC PUBLIC LICENSE OR THE GNU AGPL
 * VERSION 3, ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the OSMC (Open Source Modelica Consortium)
 * Public License (OSMC-PL) are obtained from OSMC, either from the above
 * address, from the URLs:
 * http://www.openmodelica.org or
 * https://github.com/OpenModelica/ or
 * http://www.ida.liu.se/projects/OpenModelica,
 * and in the OpenModelica distribution.
 *
 * GNU AGPL version 3 is obtained from:
 * https://www.gnu.org/licenses/licenses.html#GPL
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */

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
   bool operator< (const PerturbationRow& b) const {return (this->name < b.name);}
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
