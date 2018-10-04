#ifndef VECTORIALRESULTSDIALOG_H
#define VECTORIALRESULTSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QJsonDocument>
#include <QJsonObject>

class VectorialResultsDialog : public QDialog
{
    Q_OBJECT
public:
    VectorialResultsDialog(QJsonDocument vectorialResults, QWidget *pParent = 0);

    // Conventions:
    //   Columns ordering
    int nameColPos    = 0;
    int optimumColPos = 1;
    int defaultColPos = 2;
    int diffColPos    = 3;
private:
    // GUI members
    // x
    QLabel     *mpXLabel;
    QTableView *mpXTable;
    // f(x)
    QLabel  *mpFxLabel;
    QLabel  *mpFxValue;
    // Data members
    QJsonObject mXOptMap;
    double mFx;

};

#endif // VECTORIALRESULTSDIALOG_H
