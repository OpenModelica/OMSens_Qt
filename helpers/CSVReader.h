#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <QString>
#include <QVector>

class CSVReader
{
public:
    CSVReader();

    QString getLastRow(QString path);
    QVector<QString> getColumnsNames(QString path);
    QVector<QVector<double>> getNumericData(QString path);
    QVector<double> getColumnValues(QString path, QString columnName);
};

#endif // CSVREADER_H
