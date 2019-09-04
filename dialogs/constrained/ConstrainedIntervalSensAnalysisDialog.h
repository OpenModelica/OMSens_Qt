#ifndef CONSTRAINEDINTERVALSENSANALYSISDIALOG_H
#define CONSTRAINEDINTERVALSENSANALYSISDIALOG_H

#include <QObject>
#include <QWidget>
#include "../BaseRunSpecsDialog.h"
#include "omedit_plugin/model.h"
#include "specs/ConstrainedIntervalSpecs.h"

class ConstrainedIntervalSensAnalysisDialog : public BaseRunSpecsDialog
{
    Q_OBJECT
public:
    // Constructors
    ConstrainedIntervalSensAnalysisDialog(Model model, ConstrainedIntervalSpecs runSpecs, QWidget *pParent = 0);
    ConstrainedIntervalSensAnalysisDialog(Model model, QWidget *pParent = 0);

};

#endif // CONSTRAINEDINTERVALSENSANALYSISDIALOG_H
