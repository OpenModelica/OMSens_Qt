#include "OMSensPlugin.h"
#include "OMSensDialog.h"

QString OMSensPlugin::pluginName()
{
    return QString("OMSens");
}

void OMSensPlugin::analyzeModel(Model model)
{
    // Initialize main dialog with model
    OMSensDialog* pOmsensDialog =  new OMSensDialog(model);
    // Show dialog
    pOmsensDialog->show();
}
