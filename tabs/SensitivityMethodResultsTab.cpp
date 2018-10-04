#include "SensitivityMethodResultsTab.h"
#include <QFormLayout>
#include "../dialogs/ImageViewerDialog.h"
#include "../dialogs/CSVViewerDialog.h"

SensitivityMethodResultsTab::SensitivityMethodResultsTab(QString description, QString matrixPath, QString heatmapPath, QString columnsIDsPath, QString rowsIDsPath, QWidget *parent) : QWidget(parent)
{
    // Dialog settings
    // Description
    mpDescriptionLabel = new QLabel(tr("Description:"), this);
    mpDescriptionValue = new QLabel(description, this);
    // Heatmap
    mMatrixPath    = matrixPath;
    mHeatmapPath   = heatmapPath;
    mColumnIDsPath = columnsIDsPath;
    mRowsIDsPath   = rowsIDsPath;
    mpHeatmapLabel      = new QLabel(tr("Results:"), this);
    mpOpenMatrixButton    = new QPushButton("Matrix", this);
    mpOpenMatrixButton->setAutoDefault(true);
    mpOpenMatrixButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mpOpenHeatmapButton    = new QPushButton("Heatmap", this);
    mpOpenHeatmapButton->setAutoDefault(true);
    mpOpenHeatmapButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mpOpenColumnsIDsButton = new QPushButton("Variables IDs", this);
    mpOpenColumnsIDsButton->setAutoDefault(true);
    mpOpenColumnsIDsButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mpOpenRowsIDsButton    = new QPushButton("Parameters IDs", this);
    mpOpenRowsIDsButton->setAutoDefault(true);
    mpOpenRowsIDsButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    connect(mpOpenMatrixButton     , &QPushButton::clicked, this, &SensitivityMethodResultsTab::openMatrix);
    connect(mpOpenHeatmapButton    , &QPushButton::clicked, this, &SensitivityMethodResultsTab::openHeatmap);
    connect(mpOpenColumnsIDsButton , &QPushButton::clicked, this, &SensitivityMethodResultsTab::openColumnIDs);
    connect(mpOpenRowsIDsButton    , &QPushButton::clicked, this, &SensitivityMethodResultsTab::openRowsIDs);

    QFormLayout *mainLayout = new QFormLayout(this);
    // Description
    mainLayout->addRow(mpDescriptionLabel, mpDescriptionValue);
    // Heatmap
    QHBoxLayout *pHeatmapRowLayout = new QHBoxLayout(this);
    pHeatmapRowLayout->addWidget(mpHeatmapLabel);
    pHeatmapRowLayout->addWidget(mpOpenMatrixButton);
    pHeatmapRowLayout->addWidget(mpOpenHeatmapButton);
    pHeatmapRowLayout->addWidget(mpOpenColumnsIDsButton);
    pHeatmapRowLayout->addWidget(mpOpenRowsIDsButton);
    pHeatmapRowLayout->addStretch();
    mainLayout->addRow(pHeatmapRowLayout);

    // Layout settings
    setLayout(mainLayout);


}
// Slots
void SensitivityMethodResultsTab::openMatrix()
{
    CSVViewerDialog *pCSVDialog = new CSVViewerDialog(mMatrixPath, this);
    pCSVDialog->show();
}
void SensitivityMethodResultsTab::openHeatmap()
{
    ImageViewerDialog *pImageViewer = new ImageViewerDialog(mHeatmapPath, this);
    pImageViewer->show();
}
void SensitivityMethodResultsTab::openColumnIDs()
{
    CSVViewerDialog *pCSVDialog = new CSVViewerDialog(mColumnIDsPath, this);
    pCSVDialog->show();
}
void SensitivityMethodResultsTab::openRowsIDs()
{
    CSVViewerDialog *pCSVDialog = new CSVViewerDialog(mRowsIDsPath, this);
    pCSVDialog->show();
}
