#ifndef OMSENSDIALOG_H
#define OMSENSDIALOG_H

#include <QWidget>
#include <QDialog>
#include "OMSens/model.h"
#include <Component/Component.h>

class OMSensDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OMSensDialog(ModelWidget* currentModelWidget, QWidget *parent = nullptr);

private:
    // Data
    ModelWidget* mpCurrentModelWidget;
    // GUI
    QPushButton *mpIndivButton;
    QPushButton *mpSweepButton;
    QPushButton *mpVectButton;
    // Auxs
    QList<QString> getComponentsMatching(QList<Component*> pModelComponents, const char *variability, const char *causality, const char *className);
    Model currentModelOpen();
    bool checkIfActiveModel();

signals:

public slots:
  void runIndivSensAnalysis();
  void runMultiParameterSweep();
  void runVectorialSensAnalysis();
  void runPythonScript();
  void runCURVITestFile();
  void openSensAnalysisResult();
  void openSensAnalysisImage();
};

#endif // OMSENSDIALOG_H
