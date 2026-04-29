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

#ifndef OMSENSPLUGIN_H
#define OMSENSPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QString>
#include "../OMEdit/OMEditLIB/Interfaces/InformationInterface.h"
#include "../OMEdit/OMEditLIB/Interfaces/ModelInterface.h"

class OMSensPlugin: public QObject, public InformationInterface, public ModelInterface
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.openmodelica.OMEdit.plugins.OMSens")
  Q_INTERFACES(InformationInterface ModelInterface)

  // InformationInterface interface
public:
  static QString OpenModelicaHome;
  static QString tempPath;
  static QString OMSensBackendPath;
  static QString pythonExecPath;

  // InformationInterface interface
public:
  virtual void setOpenModelicaHome(const QString &omhome) override;
  virtual void setTempPath(const QString &path) override;
  virtual void setOMSensPath(const QString &path) override;
  virtual void setPython(const QString &path) override;

  // ModelInterface interface
public:
  virtual void analyzeModel(const QList<QVariant> &modelData) override;
};

#endif // OMSENSPLUGIN_H
