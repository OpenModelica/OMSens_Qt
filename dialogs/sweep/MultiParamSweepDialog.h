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

#ifndef MULTIPARAMSWEEPDIALOG_H
#define MULTIPARAMSWEEPDIALOG_H


#include <QDialog>
#include <QDoubleSpinBox>
#include <QFrame>
#include <QGridLayout>
#include <QTableWidget>
#include <QDialogButtonBox>
#include <QJsonObject>
#include <QString>
#include "../../tabs/SimulationTab.h"
#include "../../tabs/VariablesTab.h"
#include "../../tabs/ParametersExtendedTab.h"
#include "../../tabs/HelpTab.h"
#include "../../DualLists.h"
#include "omedit_plugin/model.h"
#include "../BaseRunSpecsDialog.h"
#include "../../specs/SweepSpecs.h"

class MultiParamSweepDialog : public BaseRunSpecsDialog
{
    Q_OBJECT
public:
    // Constructors
    MultiParamSweepDialog(Model model, SweepSpecs runSpecs, QWidget *pParent = 0);
    MultiParamSweepDialog(Model model, QWidget *pParent = 0);

    // Getters
    QJsonDocument getRunSpecifications() const;
    QString getDestFolderPath() const;

    // Conventions
    QString pythonScriptName();
    QString helpTextPath = ":/OMSens/sweep/help.html";
    // Conventions for parameters perturbation rows
    int    default_perturbation_type_id = ParametersExtendedTab::NoPerturbationId;
    int    default_iterations           = 3;
    double default_percentage           = 5;
    double default_fixed_value          = 0;

private:
    void initialize(QList<VariableInclusion> vars_inclusion, QList<PerturbationRow> pert_rows, QString modelName, QString modelFilePath, double startTime, double stopTime);
    // GUI members
    QTabWidget            *mpTabWidget;
    SimulationTab         *mpSimulationSettingsTab;
    VariablesTab          *mpVariablesTab;
    ParametersExtendedTab *mpParametersTab;
    HelpTab               *mpHelpTab;
    QDialogButtonBox      *mpButtonBox;

    // Auxs:
    void initializeWindowSettings();
    QString readHelpText();
    QStringList getVarsToAnalyze() const;
    void groupParametersPerturbationsToLists(QList<SweepingParameterPerturbation> &parametersToSweep, QList<FixedParameterPerturbation> &parametersToSetFixedValue) const;
    QList<VariableInclusion> defaultVariablesToInclude(QList<QString> variables);
    QList<PerturbationRow> defaultParametersPerturbations(QList<QString> parameters);
    QList<VariableInclusion> varsInclusionFromSuperAndSubList(QStringList exp_vars, QList<QString> model_variables);
    QList<PerturbationRow> pertRowsFromFIxedAndSweepParamsInfo(QList<FixedParameterPerturbation> fixed_params, QList<SweepingParameterPerturbation> parameters_to_sweep, QList<QString> no_pert_params);

private slots:
    void runMultiParamSweep();
};

#endif // MULTIPARAMSWEEPDIALOG_H
