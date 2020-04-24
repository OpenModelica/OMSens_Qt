#include "helpers/CSVReader.h"
#include <QFile>
#include <QDebug>
#include <vector>
#include <string>

using namespace std;

CSVReader::CSVReader()
{

}

QString CSVReader::getLastRow(QString path)
{
    QString value = "";
    QFile file(path);
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    } else {
        // Create a thread to retrieve data from a file
        QTextStream in(&file);
        QString line = in.readLine();

        while (!in.atEnd()){
          QString s = in.readLine(); // reads line from file
          value = s;
        }
        file.close();
    }
    return value;
}

QVector<QVector<double>> CSVReader::getNumericData(QString path)
{
    QVector<QVector<double>> data;
    QFile file(path);
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    } else {
        // Create a thread to retrieve data from a file
        QTextStream in(&file);
        QString line = in.readLine();

        while (!in.atEnd()){
          QString s=in.readLine(); // reads line from file
          QVector<double> row;
          for (QString elem : s.split(",")) {
              row.push_back(std::stod(elem.toStdString()));
          }
          data.push_back(row); // appends first column to list, ',' is separator
        }

        file.close();
    }
    return data;
}

QVector<double> CSVReader::getColumnValues(QString path, QString columnName)
{
    QVector<double> values;
    QFile file(path);
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    } else {
        // Create a thread to retrieve data from a file
        QTextStream in(&file);
        vector<QString> header = in.readLine().split(",").toVector().toStdVector();
        int columnIndex = 0;
        for (int i=0; i<header.size(); i++) {
            if (columnName == header[i])
                columnIndex = i;
        }

        while (!in.atEnd()){
          QString s=in.readLine(); // reads line from file
          QVector<double> row;
          vector<QString>elems = s.split(",").toVector().toStdVector();
          for (int i=0; i<elems.size(); i++) {
              if (i==columnIndex)
                values.push_back(std::stod(elems[i].toStdString()));
          }
        }

        file.close();
    }
    return values;
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
