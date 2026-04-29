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

#include "SimulationTab.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <limits>
#include <QFormLayout>
#include <QFileDialog>


SimulationTab::SimulationTab(QString modelName, QString modelFilePath, double startTime, double stopTime, QString defaultResultsFolderPath, QWidget *pParent) : QWidget(pParent)
{
    // Model name
    mpModelNameLabel = new QLabel(tr("Model:"));
    mpModelNameValue = new QLabel(modelName);
    mpModelNameValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    // Model file path
    mpModelPathLabel = new QLabel(tr("Model file:"));
    mpModelPathValue = new QLabel(modelFilePath);
    mpModelPathValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    // Results dest folder path
    mpDestFolderPathLabel = new QLabel(tr("Analysis results destination folder:"));
    mpDestFolderPathValue = new QLabel(defaultResultsFolderPath);
    mpDestFolderPathValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mpChooseDestFolderButton = new QPushButton("Choose folder");
    mpChooseDestFolderButton->setAutoDefault(true);
    mpChooseDestFolderButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpChooseDestFolderButton, SIGNAL(clicked()), this, SLOT(launchChooseFolderDialog()));

    // Start time
    mpStartTimeLabel = new QLabel(tr("Start time:"));
    mpStartTimeBox = new QDoubleSpinBox;
    mpStartTimeBox->setRange(0, std::numeric_limits<double>::max());
    mpStartTimeBox->setValue(startTime);
    // Stop time
    mpStopTimeLabel = new QLabel(tr("Stop time:"));
    mpStopTimeBox = new QDoubleSpinBox;
    mpStopTimeBox->setRange(0, std::numeric_limits<double>::max());
    mpStopTimeBox->setValue(stopTime);

   QFormLayout *mainLayout = new QFormLayout;
   // Model name
   mainLayout->addRow(mpModelNameLabel);
   mainLayout->addRow(mpModelNameValue);
   // Model path
   mainLayout->addRow(mpModelPathLabel);
   mainLayout->addRow(mpModelPathValue);
   // Results dest folder path: Label
   mainLayout->addRow(mpDestFolderPathLabel);
   // Results dest folder path: Value
   QHBoxLayout *pDestFolderRowLayout = new QHBoxLayout;
   pDestFolderRowLayout->addWidget(mpDestFolderPathValue);
   pDestFolderRowLayout->addWidget(mpChooseDestFolderButton);
   mainLayout->addRow(pDestFolderRowLayout);
   // Start time
   mainLayout->addRow(mpStartTimeLabel);
   mainLayout->addRow(mpStartTimeBox);
   // Stop time
   mainLayout->addRow(mpStopTimeLabel);
   mainLayout->addRow(mpStopTimeBox);

   // Layout settings
   setLayout(mainLayout);
}
// Slots
void SimulationTab::launchChooseFolderDialog()
{
    // Launch dialog
    QString destFolderPath = QFileDialog::getExistingDirectory(this, tr("Choose Destination Folder"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    // Save path into member variable
    mpDestFolderPathValue->setText(destFolderPath);
}


double SimulationTab::getStartTimeValue() const
{

    return mpStartTimeBox->value();
}

double SimulationTab::getStopTimeValue() const
{
    return mpStopTimeBox->value();
}

QString SimulationTab::getDestFolderPath() const
{
    return mpDestFolderPathValue->text();
}

QString SimulationTab::getModelName() const
{
    return mpModelNameValue->text();
}

QString SimulationTab::getModelPath() const
{
    return mpModelPathValue->text();
}
