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


#include "ImageViewerDialog.h"
#include <QLabel>
#include <QScrollArea>
#include <QGuiApplication>
#include <QImageReader>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QScreen>
#include <QDir>

ImageViewerDialog::ImageViewerDialog(QString filePath, QWidget *parent)
   : QDialog(parent),
     imageLabel(new QLabel),
     scrollArea(new QScrollArea)
{
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(false);

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);

    loadFile(filePath);

    // New layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    // Assign table view to layout
    mainLayout->addWidget(scrollArea);
    // Set Dialog layout
    setLayout(mainLayout);
}


bool ImageViewerDialog::loadFile(const QString &fileName)
{
     QImageReader reader(fileName);
     //reader.setAutoTransform(true);
     const QImage newImage = reader.read();
     if (newImage.isNull()) {
         QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                  tr("Cannot load %1: %2")
                                  .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
         return false;
     }

     setImage(newImage);

     setWindowFilePath(fileName);

     return true;
}

void ImageViewerDialog::setImage(const QImage &newImage)
{
    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));

    scrollArea->setVisible(true);
    imageLabel->adjustSize();
}

QStringList ImageViewerDialog::compatibleMIMETypes()
{

// Static methods (class methods)
    // Get the valid MIME types compatible with ImageViewer
    QStringList mimeTypeFilters;
    const QList< QByteArray> supportedMimeTypes = QImageReader::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
//    if (acceptMode == QFileDialog::AcceptSave)
//        dialog.setDefaultSuffix("jpg");
    return mimeTypeFilters;

}
