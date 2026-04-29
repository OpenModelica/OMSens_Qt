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

#ifndef VECTSPECS_H
#define VECTSPECS_H

#include <QString>
#include <QJsonDocument>
#include <QStringList>

// Class
class VectSpecs
{
public:
    // Constructors
    VectSpecs(QJsonDocument json_specs_doc);
    VectSpecs( QString model_file_path, QString model_name, bool maximize,
               QStringList parameters_to_perturb, double epsilon, double percentage, double start_time,
               double stop_time, QString target_var);

    // Methods
    QJsonDocument toJson();

    // Conventions
    static const QString analysis_id_str; // Defined in .cpp

    // Specification info
    QString model_file_path;
    QString model_name;
    bool maximize;
    QStringList parameters_to_perturb;
    double epsilon;
    double percentage;
    double start_time;
    double stop_time;
    QString target_var;
    QString optimTypeString(bool maximize);

private:
    // Auxs
    QList<QString> fromListOfVariantToListOfStr(QList<QVariant> listOfQVariant);
    bool ifMaximizationFromMaxOrMinStr(QString max_or_min);
};

#endif // VECTSPECS_H
