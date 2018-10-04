#include "model.h"
#include <QList>
#include <QString>
#include <QFile>

// Parametrized constructor
Model::Model(QList<QString> inputVariables, QList<QString> outputVariables, QList<QString> auxVariables, QList<QString> parameters, QString filePath, QString modelName):
  mInputVariables(inputVariables),
  mOutputVariables(outputVariables),
  mAuxVariables(auxVariables),
  mParameters(parameters),
  mFilePath(filePath),
  mModelName(modelName)
{
    // No code needed inside the class constructor for now
}

// ---- GETTERS ----
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

QString Model::getFilePath() const
{
    return mFilePath;
}

QString Model::getModelName() const
{
    return mModelName;
}
