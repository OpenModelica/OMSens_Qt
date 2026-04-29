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

#ifndef SWEEPSPECS_H
#define SWEEPSPECS_H

#include "RunSpecifications.h"
#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonArray>

// Aux structs
struct FixedParameterPerturbation {
    FixedParameterPerturbation(QString name, double value): name(name), value(value) {}
    QString name;
    double value;
};

struct SweepingParameterPerturbation {
    QString name;
    double delta_percentage;
    int iterations;
    SweepingParameterPerturbation(QString name, double delta_percentage, int iterations):
        name(name), delta_percentage(delta_percentage), iterations(iterations) {}
};
// Class
class SweepSpecs : public RunSpecifications
{
public:
    // Constructors
    SweepSpecs(QJsonDocument json_specs_doc);
    SweepSpecs(QString model_file_path, QString model_name, double start_time, double stop_time,
               QStringList vars_to_analyze, QList<SweepingParameterPerturbation> parameters_to_sweep,
               QList<FixedParameterPerturbation> fixed_params);

    // Conventions
    static const QString analysis_id_str; // Defined in .cpp

    // Methods
    QJsonDocument toJson();

    // Specification info
    QList<FixedParameterPerturbation>    fixed_params;
    QList<SweepingParameterPerturbation> parameters_to_sweep;
    QString model_file_path;
    QString model_name;
    double start_time;
    double stop_time;
    QStringList vars_to_analyze;

private:
    // Methods
    void fromJsonArrayToListOfSweepingPerts(QJsonArray params_to_sweep_jsonarray);
    QList<SweepingParameterPerturbation> fromQJsonArrayToSweepingPerts(QJsonArray sweep_params_jsonarray);
    QList<FixedParameterPerturbation> fromQJsonArrayToFixedPerts(QJsonArray fixed_params_jsonarray);
    QJsonArray fromSweepingPertsToQJsonArray(QList<SweepingParameterPerturbation> parameters_to_sweep);
    QJsonArray fromFixedPertsToQJsonArray(QList<FixedParameterPerturbation> fixed_params);
};

#endif // SWEEPSPECS_H
