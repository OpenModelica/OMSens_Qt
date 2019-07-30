#ifndef BASERESULTSDIALOG_H
#define BASERESULTSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>

class BaseResultsDialog : public QDialog
{
    Q_OBJECT
public:
    // Constructors
    BaseResultsDialog(QWidget *parent = nullptr) : QDialog(parent) {}


    // Components shared between all results dialogs
    QLabel      *mpResultsFolderPathLabel;
    QLabel      *mpResultsFolderPathValue;
    QPushButton *mpOpenResultsFolderButton;

    // Methods
    QLabel* resultsFolderLabel()
    {
        return new QLabel("Results can be found in:");
    }

    QLabel* resultsFolderPathLabel(QString resultsFolderPath)
    {
        QLabel *pFolderPathValue = new QLabel(resultsFolderPath);
        pFolderPathValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        pFolderPathValue->setTextInteractionFlags(Qt::TextSelectableByMouse);
        pFolderPathValue->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        return pFolderPathValue;
    }

   QPushButton* buttonToOpenResultsFolder()
   {
       QPushButton *pOpenButton = new QPushButton("Open");
       pOpenButton->setAutoDefault(true);
       pOpenButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
       connect(pOpenButton, &QPushButton::clicked, this, &BaseResultsDialog::fileBrowserInResultsFolder);
       return pOpenButton;
   }


public slots:
   void fileBrowserInResultsFolder(bool)
   {
       QString folderPath = mpResultsFolderPathValue->text();
       QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
   }
};

#endif // BASERESULTSDIALOG_H
