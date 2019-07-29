#include "helpers/CSVReader.h"
#include <QFile>
#include <QDebug>
#include <vector>
#include <string>

using namespace std;

CSVReader::CSVReader()
{

}

QVector<QString> CSVReader::getColumnsNames(QString path)
{
    QVector<QString> vect;
    QFile file(path);
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    } else {
        // Create a thread to retrieve data from a file
        QTextStream in(&file);
        QString line = in.readLine();

        for (QString columnName : line.split(",")) {
            vect.push_back(columnName);
        }

        file.close();
    }
    return vect;
}
