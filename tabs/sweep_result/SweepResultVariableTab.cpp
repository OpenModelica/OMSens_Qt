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

#include "SweepResultVariableTab.h"

#include <QVBoxLayout>
#include <QPushButton>

#include "../../dialogs/general/ImageViewerDialog.h"


SweepResultVariableTab::SweepResultVariableTab(QJsonObject varNameToPlotMap, QWidget *pParent) : QDialog(pParent)
{
    // Save map between variable and plot pat
    mVarNameToPlotMap = varNameToPlotMap;

    // Get the list of variables
    mVariables = mVarNameToPlotMap.keys();

    // GUI: plots chooser
    mpVariablesLabel = new QLabel("Plots:");
    mpVariablesComboBox = new QComboBox;
    foreach(const QString& var_name, mVariables) {
        mpVariablesComboBox->addItem(var_name);
    }
    mpOpenPlotButton = new QPushButton("Open");
    mpOpenPlotButton->setAutoDefault(true);
    mpOpenPlotButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpOpenPlotButton, SIGNAL(clicked()), this, SLOT(openSelectedVarPlot()));

    // Layout
    QHBoxLayout *pMainLayout = new QHBoxLayout;
    pMainLayout->addWidget(mpVariablesLabel);
    pMainLayout->addWidget(mpVariablesComboBox);
    pMainLayout->addWidget(mpOpenPlotButton);

    // Layout settings
    setLayout(pMainLayout);
}


// Slots
void SweepResultVariableTab::openSelectedVarPlot()
{
    // Get path
    QString varName = mpVariablesComboBox->currentText();
    QJsonValue varPlotPathJSONValue = mVarNameToPlotMap.value(varName);
    QString varPlotPath = varPlotPathJSONValue.toString();
    // Launch image viewer dialog
    ImageViewerDialog *pImageViewer = new ImageViewerDialog(varPlotPath,this);
    pImageViewer->show();
}
