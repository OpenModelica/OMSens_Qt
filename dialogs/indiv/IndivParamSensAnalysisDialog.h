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

#ifndef INDIVPARAMSENSANALYSISDIALOG_H
#define INDIVPARAMSENSANALYSISDIALOG_H
#include "omedit_plugin/model.h"
#include "../../tabs/VariablesTab.h"
#include "../../tabs/ParametersSimpleTab.h"
#include "../../tabs/SimulationTab.h"
#include "../../tabs/HelpTab.h"
#include "../../tabs/PerturbationTab.h"
#include "../BaseRunSpecsDialog.h"
#include "../../specs/IndivSpecs.h"

#include <QDialog>
#include <QFrame>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QJsonObject>
#include <QDialogButtonBox>

class IndivParamSensAnalysisDialog : public BaseRunSpecsDialog
{
    Q_OBJECT
public:
    // Constructors
    IndivParamSensAnalysisDialog(Model model, IndivSpecs runSpecs, QWidget *pParent = 0);
    IndivParamSensAnalysisDialog(Model model, QWidget *pParent = 0);
    // Getters
    QJsonDocument getRunSpecifications() const;
    QString getDestFolderPath() const;
    QStringList getVarsToAnalize() const;
    QStringList getParametersToPerturb() const;

    // Conventions
    QString pythonScriptName();

private:
    // GUI members
    QTabWidget          *mpTabWidget;
    SimulationTab       *mpSimulationSettingsTab;
    VariablesTab        *mpVariablesTab;
    ParametersSimpleTab *mpParametersTab;
    HelpTab             *mpHelpTab;
    PerturbationTab     *mpPerturbationTab;
    QDialogButtonBox    *mpButtonBox;

    // Conventions
    QString helpTextPath = ":/OMSens/indiv/help.html";

    // Auxs
    void initialize(QList<VariableInclusion> vars_to_include, QList<ParameterInclusion> parameters, QString modelName, QString modelFilePath, double percentage, double startTime, double stopTime);
    void initializeWindowSettings();
    void setHeading();
    void initializeFormInputsAndLabels(const double min_perturbation_perc, const double max_perturbation_perc, const double max_target_time, const QVector<QString> methods);
    void initializeButton();
    void addWidgetsToLayout(QGridLayout *pMainLayout);
    QGridLayout * initializeLayout();
    QList<QString> fromListOfVariantToListOfStr(QList<QVariant> listOfQVariant);
    QString readHelpText();
    QList<VariableInclusion> defaultVariablesToInclude(QList<QString> variables);
    QList<ParameterInclusion> defaultParametersToInclude(QList<QString> parameters);
    QList<VariableInclusion> varsInclusionFromSuperAndSubList(QStringList exp_vars, QList<QString> model_variables);
    QList<ParameterInclusion> paramsInclusionFromSuperAndSubList(QStringList exp_params, QList<QString> model_parameters);


private slots:
  void runIndivParamSensAnalysis();
};

#endif // INDIVPARAMSENSANALYSISDIALOG_H
