#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include <QString>
#include <QFile>
#include <QJsonDocument>

class Model
{
public:
  // Constructor
  Model(QJsonDocument model_info_json);
  Model(QList<QString> inputVariables, QList<QString> outputVariables, QList<QString> auxVariables, QList<QString> parameters, QString filePath, QString modelName);
  // Getters
  QList<QString> getInputVariables() const;
  QList<QString> getOutputVariables() const;
  QList<QString> getAuxVariables() const;
  QList<QString> getParameters() const;
  QString        getFilePath() const;
  QString        getModelName() const;
  // To JSON
  QJsonDocument  toJson();

private:
  QList<QString> mInputVariables;
  QList<QString> mOutputVariables;
  QList<QString> mAuxVariables;
  QList<QString> mParameters;
  QString        mFilePath;
  QString        mModelName;
};

#endif // MODEL_H
