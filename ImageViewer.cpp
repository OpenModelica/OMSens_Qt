
#include "ImageViewer.h"
#include <QLabel>
#include <QScrollArea>
#include <QGuiApplication>
#include <QImageReader>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QScreen>
#include <QDir>

ImageViewer::ImageViewer(QWidget *parent)
   : imageLabel(new QLabel),
     scrollArea(new QScrollArea),
     QDialog(parent)
{
    // Ask for file path using dialog
    QString filePath = QFileDialog::getOpenFileName(this,tr("Open Sens Analysis Results"), "", tr("Images (*.png)"));
    // Check if the user selected a file or if they clicked cancel
    if (!filePath.isNull()){
        // Initialize Results dialog
        ImageViewer *pImageViewer = new ImageViewer(filePath);
        pImageViewer->exec();
    }
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(false);

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);

    loadFile(filePath);

    // New layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    // Assign table view to layout
    mainLayout->addWidget(scrollArea);
    // Set Dialog layout
    setLayout(mainLayout);
}


bool ImageViewer::loadFile(const QString &fileName)
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

void ImageViewer::setImage(const QImage &newImage)
{
    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));

    scrollArea->setVisible(true);
    imageLabel->adjustSize();
}
