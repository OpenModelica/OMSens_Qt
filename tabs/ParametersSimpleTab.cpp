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

#include "ParametersSimpleTab.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QHeaderView>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>

ParametersSimpleTab::ParametersSimpleTab(QList<ParameterInclusion> params_inclusion, QString quickExplanation, QWidget *parent) : QWidget(parent)
{
  paramColPos = 0;
  cboxColPos  = 1;
  // Initialize label with brief description of the analysis
  mpBriefDescriptionLabel = new QLabel(quickExplanation,this);


  //Initialize table header
  mpParametersTable = new QTableWidget(0, 2);
  const QList<QString> tableHeaders( QList<QString>()
                                     << "Parameter"
                                     << "Perturb?"
                                     );
  mpParametersTable->setHorizontalHeaderLabels(tableHeaders);
  // Declare the QPair outside the foreach because the commas are ambigous for Qt's macro
  foreach (ParameterInclusion param_include, params_inclusion)
  {
    // Add a row
    // Row index to add row to
    const int rowNum = mpParametersTable->rowCount();
    // Add "blank" row
    mpParametersTable->insertRow(rowNum);
    // Fill blank row with values corresponding to this variable
    // Set parameter name
    QLabel *paramNameWidget = new QLabel(param_include.name);
    mpParametersTable->setCellWidget(rowNum,paramColPos, paramNameWidget);
    // Set checkbox
    QCheckBox *includeCheckBox = new QCheckBox;
    includeCheckBox->setChecked(param_include.include);
    mpParametersTable->setCellWidget(rowNum,cboxColPos,includeCheckBox);
  }
  // Set table settings
  // Resize columns to contents
  mpParametersTable->resizeColumnsToContents();

  QVBoxLayout *mainLayout = new QVBoxLayout;
  // Parameters table/list
  mainLayout->addWidget(mpParametersTable);
  // Description
  mainLayout->addWidget(mpBriefDescriptionLabel);
  setLayout(mainLayout);
}

QTableWidget *ParametersSimpleTab::getParametersTable() const
{
  return mpParametersTable;
}
