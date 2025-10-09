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
