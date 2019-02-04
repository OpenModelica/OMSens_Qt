#ifndef OMSENSPLUGIN_H
#define OMSENSPLUGIN_H

#include "interfaces.h"
#include "model.h"

#include <QObject>
#include <QWidget>
#include <QtPlugin>
#include <QString>


class OMSensPlugin: public QWidget, public PluginInformationInterface, public ModelAnalysisInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.omedit.plugins.OMSens")
    Q_INTERFACES(PluginInformationInterface ModelAnalysisInterface)

public:
    QString pluginName() override;
    void analyzeModel(Model model) override;
};

#endif // OMSENSPLUGIN_H
