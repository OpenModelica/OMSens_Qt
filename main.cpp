#include "OMSensDialog.h"
#include "omedit_plugin/model.h"

#include "dialogs/indiv/IndivSensAnalTypeDialog.h"
#include "dialogs/indiv/IndivParamSensAnalysisDialog.h"
#include "dialogs/indiv/IndivSensResultsDialog.h"
#include "dialogs/sweep/MultiParamSweepDialog.h"
#include "dialogs/sweep/SweepResultDialog.h"
#include "dialogs/vect/VectorialParamSensAnalysisDialog.h"
#include "dialogs/vect/VectorialResultsDialog.h"
#include "dialogs/general/ImageViewerDialog.h"
#include "dialogs/general/CSVViewerDialog.h"
#include "dialogs/BaseRunSpecsDialog.h"
#include "dialogs/BaseResultsDialog.h"
#include "dialogs/help/HelpBrowser.h"
#include "specs/IndivSpecs.h"
#include "specs/SweepSpecs.h"
#include "specs/VectSpecs.h"

#include <QApplication>
#include <QTemporaryDir>
#include <QProcess>
#include <QProgressDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QDateTime>

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

    Model model = modelExample();

    // Initialize main dialog with model
    OMSensDialog* pOmsensDialog =  new OMSensDialog(model);
    pOmsensDialog->show();

    return a.exec();
}
