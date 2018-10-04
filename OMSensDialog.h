#ifndef OMSENSDIALOG_H
#define OMSENSDIALOG_H

#include <QWidget>
#include <QDialog>
#include "model.h"

class OMSensDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OMSensDialog(Model model, QWidget *parent = nullptr);

private:
    // Data
    Model model;
    // GUI
    QPushButton *mpIndivButton;
    QPushButton *mpSweepButton;
    QPushButton *mpVectButton;
    // Auxs

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
