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

#include "VariablesTab.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QHeaderView>
#include <QLabel>

// Constructors
VariablesTab::VariablesTab(QList<VariableInclusion> vars_inclusion, QWidget *parent) : QWidget(parent)
{
    mpVariablesTable = new QTableWidget(0, 2);
    const QList<QString> tableHeaders( QList<QString>()
                                     << "Variable"
                                     << "analyze?"
                                     );
    mpVariablesTable->setHorizontalHeaderLabels(tableHeaders);

    foreach (VariableInclusion var_include, vars_inclusion)
    {
        // Add a row
        // Row index to add row to
        const int rowNum = mpVariablesTable->rowCount();
        // Add "blank" row
        mpVariablesTable->insertRow(rowNum);
        // Fill blank row with values corresponding to this variable
        // Set variable name
        QLabel *varNameWidget = new QLabel(var_include.name);
        mpVariablesTable->setCellWidget(rowNum,varColPos, varNameWidget);
        // Set checkbox
        // Wrap the checkbox in a generic QWidget so we can set a layout to center it in the cell
        QCheckBox *includeCheckBox = new QCheckBox;
        includeCheckBox->setChecked(var_include.include);
        mpVariablesTable->setCellWidget(rowNum,cboxColPos,includeCheckBox);
    }
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mpVariablesTable);
    setLayout(mainLayout);
}

// Methods
QTableWidget *VariablesTab::getVariablesTable() const
{
    return mpVariablesTable;
}
