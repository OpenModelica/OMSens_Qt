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

#include "IndivSensAnalTypeDialog.h"
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>

IndivSensAnalTypeDialog::IndivSensAnalTypeDialog(Model model, QWidget *parent) : QDialog(parent)
{

    // Dialog settings
    setMinimumWidth(400);
    // Initialize label
    mpChooseAnalysisLabel = new QLabel("Choose between runnning a predefined analysis for World3 or a new one for the model currently active. ");
    // Initialize buttons
    mpRunW3SampleButton    = new QPushButton("Run World3 Analysis Example");
    mpRunW3SampleButton->setAutoDefault(true);
    mpRunW3SampleButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mpRunOpenModelButton    = new QPushButton;
    mpRunOpenModelButton->setAutoDefault(true);
    mpRunOpenModelButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    // The pointer is not null, so get the model name
    QString modelName = model.getModelName();
    QString enabledButtonText = "Run analysis on model: " + modelName;
    mpRunOpenModelButton->setText(enabledButtonText);
    mpRunOpenModelButton->setEnabled(true);

    connect(mpRunW3SampleButton     , &QPushButton::clicked, this, &IndivSensAnalTypeDialog::chooseW3Sample);
    connect(mpRunOpenModelButton    , &QPushButton::clicked, this, &IndivSensAnalTypeDialog::chooseOpenModel);

    // Dialog settings
    setWindowTitle("Choose Analysis Specifications");
    // Layout
    QFormLayout *mainLayout = new QFormLayout;
    // Add label
    mainLayout->addWidget(mpChooseAnalysisLabel);
    // Add buttons
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(mpRunW3SampleButton);
    buttonsLayout->addWidget(mpRunOpenModelButton);
    mainLayout->addRow(buttonsLayout);
    mainLayout->setAlignment(buttonsLayout,Qt::AlignCenter);

    setLayout(mainLayout);
}
void IndivSensAnalTypeDialog::chooseW3Sample()
{
    choseW3InsteadOfOpenModel = true;
    accept();
}

void IndivSensAnalTypeDialog::chooseOpenModel()
{
    choseW3InsteadOfOpenModel = false;
    accept();
}
