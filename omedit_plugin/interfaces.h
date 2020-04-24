#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>
#include "model.h"

class QImage;
class QPainter;
class QWidget;
class QPainterPath;
class QPoint;
class QRect;
class QString;
class QStringList;

class PluginInformationInterface
{
public:
    virtual ~PluginInformationInterface() {}

    virtual QString pluginName() = 0;
};

class ModelAnalysisInterface
{
public:
    virtual ~ModelAnalysisInterface() {}

    virtual void analyzeModel(Model model) = 0;
};


#define PluginInformationInterface_iid "org.omedit.interfaces.PluginInformationInterface/1.0"

Q_DECLARE_INTERFACE(PluginInformationInterface, PluginInformationInterface_iid)

#define ModelAnalysisInterface_iid "org.omedit.interfaces.ModelAnalysisInterface/1.0"

Q_DECLARE_INTERFACE(ModelAnalysisInterface, ModelAnalysisInterface_iid)


#endif // INTERFACES_H
