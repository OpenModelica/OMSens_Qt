#include "OMSensDialog.h"
#include "model.h"

#include <QApplication>
#include <QTemporaryDir>


// Model example to be used when OMSens is used as standalone
// (main function below example)
Model modelExample()
{
  // Define model data
  const QList<QString> inputVariables;
  const QList<QString> parameters( QList<QString>()
                                   << "realParam1"
                                   << "realParam2"
                                   << "realParam3");
  const QList<QString> outputVariables( QList<QString>()
                                   << "outvar1"
                                   << "outvar2"
                                   << "outvar3");
  const QList<QString> auxVariables;

  // Model name
  QString modelName = "ModelWithVariousParams";
  // Model path in Qt resources
  QString fileResourcePath = ":/OMSens/ModelWithVariousParams.mo";
  // Model file name to be used when written to disk
  QString tempModelName = "ModelWithVariousParams.mo";
  // Temp dir where to write Model
  QTemporaryDir tempDir;
  // Disable auto remove so the user can check the model
  tempDir.setAutoRemove(false);
  QString  filePath=  QDir::cleanPath(tempDir.path() + QDir::separator() + tempModelName);
  if (tempDir.isValid()) {
    QFile::copy(fileResourcePath, filePath);
  }
  // Initialize model
  Model model(inputVariables, outputVariables, auxVariables, parameters, filePath, modelName);

  return model;
}

int main(int argc, char *argv[])
{
    // Initialize Qt Application
    QApplication a(argc, argv);
    // Model information for testing:
    Model model = modelExample();
    // Initialize OMSens Dialog
    OMSensDialog dialog(model);
    // Show OMSens Dialog
    dialog.show();
    // Run and end Qt Application
    return a.exec();
}
