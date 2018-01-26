#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include <QString>
#include <QFile>

class Model
{
public:
  Model(QList<QString> inputVariables, QList<QString> outputVariables, QList<QString> auxVariables, QList<QString> parameters);
  QList<QString> getInputVariables() const;
  QList<QString> getOutputVariables() const;
  QList<QString> getAuxVariables() const;
  QList<QString> getParameters() const;

// We don't use the file for now. When the time comes,
//   decide what to store:
//   1) QString filePath
//   2) QFile filePath and return QString filePath
//   3) QFile file and return QFile file
//  QFile          getFile() const;

private:
  QList<QString> mInputVariables;
  QList<QString> mOutputVariables;
  QList<QString> mAuxVariables;
  QList<QString> mParameters;
// We don't use the file for now. When the time comes,
//   decide what to store:
//   1) QString filePath
//   2) QFile filePath and return QString filePath
//   3) QFile file and return QFile file
//  QFile          mFile;
};

#endif // MODEL_H
