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

#include "PerturbationTab.h"

#include <QGridLayout>
#include <limits>

PerturbationTab::PerturbationTab(double percentage, QWidget *parent) : QTabWidget(parent)
{
    // Perturbation
    mpPerturbationLabel = new QLabel(tr("Perturbation (choose + or -):"));
    mpPerturbationBox = new ForceSignDoubleSpinbox;
    mpPerturbationBox->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    mpPerturbationBox->setValue(percentage);
    mpPerturbationBox->setSuffix("%");

    // Layout
    QGridLayout *pMainLayout = new QGridLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    // Perturbation
    pMainLayout->addWidget(mpPerturbationLabel,0,0);
    pMainLayout->addWidget(mpPerturbationBox  ,0,1);

    // Layout settings
    setLayout(pMainLayout);

}

double PerturbationTab::getPerturbationValue() const
{
    return mpPerturbationBox->value();
}
