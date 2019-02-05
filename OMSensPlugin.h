#ifndef OMSENSPLUGIN_H
#define OMSENSPLUGIN_H

#include "omedit_plugin/interfaces.h"
#include "omedit_plugin/model.h"

#include <QObject>
#include <QtPlugin>
#include <QString>


class OMSensPlugin: public QObject, public PluginInformationInterface, public ModelAnalysisInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.omedit.plugins.OMSens")
    Q_INTERFACES(PluginInformationInterface ModelAnalysisInterface)

public:
    QString pluginName() override;
    void analyzeModel(Model model) override;
};

#endif // OMSENSPLUGIN_H
