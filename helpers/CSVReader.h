#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <QString>
#include <QVector>

class CSVReader
{
public:
    CSVReader();

    QVector<QString> getColumnsNames(QString path);
};

#endif // CSVREADER_H
