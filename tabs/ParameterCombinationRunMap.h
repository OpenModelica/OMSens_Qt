#ifndef PARAMETERCOMBINATIONRUNMAP_H
#define PARAMETERCOMBINATIONRUNMAP_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>

class ParameterCombinationRunMap : public QWidget
{
    Q_OBJECT
public:
    ParameterCombinationRunMap(QString mOMSensResultsPath, QWidget *parent = 0);
};

#endif // PARAMETERCOMBINATIONRUNMAP_H
