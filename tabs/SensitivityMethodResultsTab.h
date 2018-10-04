#ifndef SENSITIVITYMETHODRESULTSTAB_H
#define SENSITIVITYMETHODRESULTSTAB_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPushButton>

class SensitivityMethodResultsTab : public QWidget
{
    Q_OBJECT
public:
    explicit SensitivityMethodResultsTab(QString description, QString matrixPath, QString heatmapPath, QString columnsIDsPath, QString rowsIDsPath, QWidget *parent = 0);

private:
    // Data
    QString mMatrixPath;
    QString mHeatmapPath;
    QString mColumnIDsPath;
    QString mRowsIDsPath;
    // GUI
    QLabel *mpDescriptionLabel;
    QLabel *mpDescriptionValue;
    QLabel *mpHeatmapLabel;
    QPushButton *mpOpenMatrixButton;
    QPushButton *mpOpenHeatmapButton;
    QPushButton *mpOpenColumnsIDsButton;
    QPushButton *mpOpenRowsIDsButton;

signals:

private slots:
    void openMatrix();
    void openHeatmap();
    void openColumnIDs();
    void openRowsIDs();
};

#endif // SENSITIVITYMETHODRESULTSTAB_H
