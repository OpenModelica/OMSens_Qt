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

#ifndef VECTORIALPARAMSENSANALYSISDIALOG_H
#define VECTORIALPARAMSENSANALYSISDIALOG_H

#include <QDialog>
#include <QFrame>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QJsonObject>
#include "omedit_plugin/model.h"
#include "../../tabs/SimulationTab.h"
#include "../../tabs/ParametersSimpleTab.h"
#include "../../tabs/OptimizationTab.h"
#include "../../tabs/HelpTab.h"
#include "../BaseRunSpecsDialog.h"
#include "../../specs/VectSpecs.h"

class VectorialSensAnalysisDialog : public BaseRunSpecsDialog
{
    Q_OBJECT
public:
    // Constructors
    VectorialSensAnalysisDialog(Model model, VectSpecs runSpecs, QWidget *pParent = 0);
    VectorialSensAnalysisDialog(Model model, QWidget *pParent = 0);
    // Getters
    QJsonDocument getRunSpecifications() const;
    QString getDestFolderPath() const;
    // Conventions
    QString pythonScriptName();

private:
    void initialize(QList<QString> variables, QString target_var, bool maximize, double epsilon, QList<ParameterInclusion> params_inclusion, QString modelName, QString modelFilePath, double percentage, double startTime, double stopTime);
    // GUI members
    QTabWidget            *mpTabWidget;
    SimulationTab         *mpSimulationSettingsTab;
    ParametersSimpleTab   *mpParametersTab;
    OptimizationTab       *mpOptimizationTab;
    HelpTab               *mpHelpTab;
    QDialogButtonBox      *mpButtonBox;

    // Conventions
    QString helpTextPath = ":/OMSens/vect/help.html";

    // Aux functions
    void initializeWindowSettings();
    QString readHelpText();
    QList<ParameterInclusion> defaultParametersToInclude(QList<QString> parameters);
    QList<ParameterInclusion> paramsInclusionFromSuperAndSubList(QStringList exp_params, QList<QString> model_parameters);
    QStringList getParametersToPerturb() const;
    bool getIfMaximization() const;

private slots:
    void runVectorialParamSensAnalysis();
};

#endif // VECTORIALPARAMSENSANALYSISDIALOG_H
