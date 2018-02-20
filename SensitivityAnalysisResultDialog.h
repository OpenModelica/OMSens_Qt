#ifndef SENSITIVITYANALYSISRESULTDIALOG_H
#define SENSITIVITYANALYSISRESULTDIALOG_H

#include <QDialog>
#include <QFile>
#include <QTableView>

class SensitivityAnalysisResultDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SensitivityAnalysisResultDialog(QString filePath, QWidget *parent = 0);
private:
    QTableView* mpResultsTable;

signals:

public slots:
};

#endif // SENSITIVITYANALYSISRESULTDIALOG_H
