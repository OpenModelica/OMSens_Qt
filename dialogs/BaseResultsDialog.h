/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-2026, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF AGPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.8.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES
 * RECIPIENT'S ACCEPTANCE OF THE OSMC PUBLIC LICENSE OR THE GNU AGPL
 * VERSION 3, ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the OSMC (Open Source Modelica Consortium)
 * Public License (OSMC-PL) are obtained from OSMC, either from the above
 * address, from the URLs:
 * http://www.openmodelica.org or
 * https://github.com/OpenModelica/ or
 * http://www.ida.liu.se/projects/OpenModelica,
 * and in the OpenModelica distribution.
 *
 * GNU AGPL version 3 is obtained from:
 * https://www.gnu.org/licenses/licenses.html#GPL
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */

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
    BaseResultsDialog(QWidget *parent = 0) : QDialog(parent) {}

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
       QString folderPath =mpResultsFolderPathValue->text();
       QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
   }
};

#endif // BASERESULTSDIALOG_H
