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

#ifndef VECTORIALRESULTSDIALOG_H
#define VECTORIALRESULTSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTabWidget>
#include <QDialogButtonBox>

#include "../../tabs/optim_result/OptimizationResultParametersTab.h"
#include "../../tabs/optim_result/OptimizationResultOtherTab.h"
#include "../BaseResultsDialog.h"

class VectorialResultsDialog : public BaseResultsDialog
{
    Q_OBJECT
public:
    VectorialResultsDialog(QJsonDocument vectorialResults, QString resultsFolderPath, QWidget *pParent = 0);
private:
    // GUI (there are some components defined in the superclass)
    QTabWidget            *mpTabWidget;
    OptimizationResultParametersTab* mpOptimParamsTab;
    OptimizationResultOtherTab*      mpOptimOtherTab;
    QDialogButtonBox   *mpButtonBox;
    // Plot
    QLabel      *mpFxPlotLabel;
    QPushButton *mpOpenPlotButton;
    // stoptime
    QLabel *mpStopTimeLabel;
    QLabel *mpStopTimeValue;
    // Data
    double mStopTime;
    QString mPlotPath;

    // Aux functions
    void initializeWindowSettings();

private slots:
    void openPlot();
};

#endif // VECTORIALRESULTSDIALOG_H
