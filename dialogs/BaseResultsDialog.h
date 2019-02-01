#ifndef BASERESULTSDIALOG_H
#define BASERESULTSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QString>

class BaseResultsDialog : public QDialog
{
    Q_OBJECT
public:
    BaseResultsDialog(QWidget *parent = nullptr) : QDialog(parent) {}

    QLabel* folderPathLabel()
    {
        return new QLabel("Results can be found in:");
    }

    QLabel* folderPathValue(QString resultsFolderPath)
    {
        QLabel *pFolderPathValue = new QLabel(resultsFolderPath);
        pFolderPathValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        pFolderPathValue->setTextInteractionFlags(Qt::TextSelectableByMouse);
        return pFolderPathValue;
    }

signals:

public slots:
};

#endif // BASERESULTSDIALOG_H
