#ifndef GENERALSETTINGS_H
#define GENERALSETTINGS_H

#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLineEdit>

class SimulationTab : public QWidget
{
    Q_OBJECT
public:
    explicit SimulationTab(QString modelName, QString modelFilePath, double startTime, double stopTime,
                           QString defaultResultsFolderPath, QWidget *parent = 0);
    // Getters
    double  getStartTimeValue() const;
    double  getStopTimeValue() const;
    QString getDestFolderPath() const;
    QString getRestrictionPath() const;

    QString getModelName() const;

    QString getModelPath() const;

private:
    // Model name
    QLabel *mpModelNameLabel;
    QLabel *mpModelNameValue;
    // Model file path
    QLabel *mpModelPathLabel;
    QLabel *mpModelPathValue;
    // Results dest folder path
    QLabel *mpDestFolderPathLabel;
    QLabel *mpDestFolderPathValue;
    QPushButton *mpChooseDestFolderButton;

    // Start time
    QLabel *mpStartTimeLabel;
    QDoubleSpinBox *mpStartTimeBox;
    // Stop time
    QLabel *mpStopTimeLabel;
    QDoubleSpinBox *mpStopTimeBox;
    // Intermediate results path
    QLineEdit *mpIntermediateResultPath;


signals:

private slots:
    void launchChooseFolderDialog();
};

#endif // GENERALSETTINGS_H
