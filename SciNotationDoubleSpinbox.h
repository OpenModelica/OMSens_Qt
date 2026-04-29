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

#ifndef SCINOTDOUBLESPINBOX_H
#define SCINOTDOUBLESPINBOX_H

#include <QObject>
#include <QDoubleSpinBox>

class SciNotationDoubleSpinbox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit SciNotationDoubleSpinbox(QWidget *parent = 0) : QDoubleSpinBox(parent) {}

    // Change the way we read the user input
    double valueFromText(const QString & text) const
    {
        double numFromStr = text.toDouble(); return numFromStr; }

    // Change the way we show the internal number
    QString textFromValue(double value) const
    {
        return QString::number(value, 'E', 6);
    }

    // Change the way we validate user input (if validate => valueFromText)
    QValidator::State validate(QString &text, int&) const
    {

        // Try to convert the string to double
        bool ok;
        text.toDouble(&ok);
        // See if it's a valid Double
        QValidator::State validationState;
        if(ok)
        {
            // If string conversion was valid, set as ascceptable
            validationState = QValidator::Acceptable;

        }
        else
        {
            // If string conversion was invalid, set as invalid
            validationState = QValidator::Invalid;
        }
        return validationState;
    }



signals:

public slots:
};

#endif // SCINOTDOUBLESPINBOX_H
