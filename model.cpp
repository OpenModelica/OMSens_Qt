#include "model.h"
#include <QList>
#include <QString>
#include <QFile>

Model::Model(QList<QString> inputVariables, QList<QString> outputVariables, QList<QString> auxVariables, QList<QString> parameters):
  mInputVariables(inputVariables),
  mOutputVariables(outputVariables),
  mAuxVariables(auxVariables),
  mParameters(parameters)
  //mFile(filePath)
{
    // No code needed inside the class constructor for now
}

QList<QString> Model::getInputVariables() const
{
    return mInputVariables;
}

QList<QString> Model::getOutputVariables() const
{
    return mOutputVariables;
}

QList<QString> Model::getAuxVariables() const
{
    return mAuxVariables;
}

QList<QString> Model::getParameters() const
{
    return mParameters;
}

// We don't use the file for now. When the time comes,
//   decide what to store:
//   1) QString filePath
//   2) QFile filePath and return QString filePath
//   3) QFile file and return QFile file
//QFile Model::getFile() const
//{
//    return mFile;
//}
