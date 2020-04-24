#include "dialogs/constrained/ConstrainedIntervalSensAnalysisDialog.h"
#include "specs/ConstrainedIntervalSpecs.h"
#include "omedit_plugin/model.h"

ConstrainedIntervalSensAnalysisDialog::ConstrainedIntervalSensAnalysisDialog(Model model, ConstrainedIntervalSpecs runSpecs, QWidget *pParent)
  : BaseRunSpecsDialog(pParent)
{

}

ConstrainedIntervalSensAnalysisDialog::ConstrainedIntervalSensAnalysisDialog(Model model, QWidget *pParent)
  : BaseRunSpecsDialog(pParent)
{

}
