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

#include "SensitivityMethodResultsTab.h"
#include <QFormLayout>
#include "../dialogs/general/ImageViewerDialog.h"
#include "../dialogs/general/CSVViewerDialog.h"

SensitivityMethodResultsTab::SensitivityMethodResultsTab(QString description, QString matrixPath, QString heatmapPath, QString columnsIDsPath, QString rowsIDsPath, QWidget *parent) : QWidget(parent)
{
    // Dialog settings
    // Description
    mpDescriptionLabel = new QLabel(tr("Description:"));
    mpDescriptionValue = new QLabel(description);
    // Heatmap
    mMatrixPath    = matrixPath;
    mHeatmapPath   = heatmapPath;
    mColumnIDsPath = columnsIDsPath;
    mRowsIDsPath   = rowsIDsPath;
    mpHeatmapLabel      = new QLabel(tr("Results:"));
    mpOpenMatrixButton    = new QPushButton("Matrix");
    mpOpenMatrixButton->setAutoDefault(true);
    mpOpenMatrixButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mpOpenHeatmapButton    = new QPushButton("Heatmap");
    mpOpenHeatmapButton->setAutoDefault(true);
    mpOpenHeatmapButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mpOpenColumnsIDsButton = new QPushButton("State Variable IDs");
    mpOpenColumnsIDsButton->setAutoDefault(true);
    mpOpenColumnsIDsButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mpOpenRowsIDsButton    = new QPushButton("Parameter IDs");
    mpOpenRowsIDsButton->setAutoDefault(true);
    mpOpenRowsIDsButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    connect(mpOpenMatrixButton     , &QPushButton::clicked, this, &SensitivityMethodResultsTab::openMatrix);
    connect(mpOpenHeatmapButton    , &QPushButton::clicked, this, &SensitivityMethodResultsTab::openHeatmap);
    connect(mpOpenColumnsIDsButton , &QPushButton::clicked, this, &SensitivityMethodResultsTab::openColumnIDs);
    connect(mpOpenRowsIDsButton    , &QPushButton::clicked, this, &SensitivityMethodResultsTab::openRowsIDs);

    QFormLayout *mainLayout = new QFormLayout;
    // Description
    mainLayout->addRow(mpDescriptionLabel, mpDescriptionValue);
    // Heatmap
    QHBoxLayout *pHeatmapRowLayout = new QHBoxLayout;
    pHeatmapRowLayout->addWidget(mpHeatmapLabel);
    pHeatmapRowLayout->addWidget(mpOpenMatrixButton);
    pHeatmapRowLayout->addWidget(mpOpenHeatmapButton);
    pHeatmapRowLayout->addWidget(mpOpenColumnsIDsButton);
    pHeatmapRowLayout->addWidget(mpOpenRowsIDsButton);
    pHeatmapRowLayout->addStretch();
    mainLayout->addRow(pHeatmapRowLayout);

    // Layout settings
    setLayout(mainLayout);


}
// Slots
void SensitivityMethodResultsTab::openMatrix()
{
    CSVViewerDialog *pCSVDialog = new CSVViewerDialog(mMatrixPath, this);
    pCSVDialog->show();
}
void SensitivityMethodResultsTab::openHeatmap()
{
    ImageViewerDialog *pImageViewer = new ImageViewerDialog(mHeatmapPath, this);
    pImageViewer->show();
}
void SensitivityMethodResultsTab::openColumnIDs()
{
    CSVViewerDialog *pCSVDialog = new CSVViewerDialog(mColumnIDsPath, this);
    pCSVDialog->show();
}
void SensitivityMethodResultsTab::openRowsIDs()
{
    CSVViewerDialog *pCSVDialog = new CSVViewerDialog(mRowsIDsPath, this);
    pCSVDialog->show();
}
