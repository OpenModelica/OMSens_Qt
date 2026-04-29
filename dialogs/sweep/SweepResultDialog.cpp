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

#include "SweepResultDialog.h"

#include <QWidget>
#include <QJsonObject>
#include <QFormLayout>
#include <QPushButton>

SweepResultsDialog::SweepResultsDialog(QJsonDocument sweepResults, QString resultsFolderPath, QWidget *pParent) : BaseResultsDialog(pParent)
{
    // Parse JSON
    // Get the "main" object of the json document
    QJsonObject sweepResultsObject = sweepResults.object();
    // Get the <var name> to <plot path> mapper
    mVarNameToPlotMap = sweepResultsObject.value(QString("sweep_plots")).toObject();

    // Tabs
    mpVariablesResultTab = new SweepResultVariableTab(mVarNameToPlotMap);

    // Tabs container
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpVariablesResultTab, tr("Variables"));

    // Results folder (defined in superclass)
    mpResultsFolderPathLabel  = resultsFolderLabel();
    mpResultsFolderPathValue  = resultsFolderPathLabel(resultsFolderPath);
    mpOpenResultsFolderButton = buttonToOpenResultsFolder();

    // Buttons
    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("Ok", QDialogButtonBox::AcceptRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &SweepResultsDialog::accept);

    // Dialog settings
    setWindowTitle("Multiparameter Sweep Results");
    // Layout
    QVBoxLayout *pMainLayout = new QVBoxLayout;

    // Tabs group
    pMainLayout->addWidget(mpTabWidget);

    // Results folder path
    QGridLayout *resultsFolderLayout = new QGridLayout;
    resultsFolderLayout->addWidget(mpResultsFolderPathLabel, 0, 0);
    resultsFolderLayout->addWidget(mpResultsFolderPathValue, 1, 0);
    resultsFolderLayout->addWidget(mpOpenResultsFolderButton, 1, 1);
    pMainLayout->addLayout(resultsFolderLayout);

    // Accept button
    pMainLayout->addWidget(mpButtonBox, 0, Qt::AlignCenter);

    // Layout settings
    setLayout(pMainLayout);
}
