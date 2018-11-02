#include "VectorialResultsDialog.h"

#include <QJsonObject>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "../../dialogs/general/ImageViewerDialog.h"


VectorialResultsDialog::VectorialResultsDialog(QJsonDocument vectorialResults, QString resultsFolderPath, QWidget *pParent) : BaseResultsDialog(pParent)
{
    // Parse JSON
    // Get the "main" object of the json document
    QJsonObject vectorialResultsObject = vectorialResults.object();
    // Get data
    mStopTime = vectorialResultsObject.value(QString("stop_time")).toDouble();
    mPlotPath = vectorialResultsObject.value(QString("plot_path")).toString();

    // Initialize tabs
    mpOptimParamsTab = new OptimizationResultParametersTab(vectorialResults);
    mpOptimOtherTab = new OptimizationResultOtherTab(vectorialResults);
    // Initialize tabs container widget
    mpTabWidget = new QTabWidget;
    mpTabWidget->addTab(mpOptimParamsTab, tr("Parameters"));
    mpTabWidget->addTab(mpOptimOtherTab, tr("Variable"));

    // Plot
    mpFxPlotLabel = new QLabel("Plot:");
    mpOpenPlotButton = new QPushButton("Open");
    mpOpenPlotButton->setAutoDefault(true);
    mpOpenPlotButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(mpOpenPlotButton, SIGNAL(clicked()), this, SLOT(openPlot()));

    // Stop time
    mpStopTimeLabel = new QLabel("Stop time:");
    mpStopTimeValue = new QLabel(QString::number(mStopTime));
    //mpStopTimeValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    // Results folder
    mpResultsFolderPathLabel = new QLabel("Results can be found in:");
    mpResultsFolderPathValue = new QLabel(resultsFolderPath);
    mpResultsFolderPathValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mpResultsFolderPathValue->setTextInteractionFlags(Qt::TextSelectableByMouse);

    // Buttons
    mpButtonBox = new QDialogButtonBox;
    mpButtonBox->addButton("Ok", QDialogButtonBox::AcceptRole);
    connect(mpButtonBox, &QDialogButtonBox::accepted, this, &VectorialResultsDialog::accept);

    // Layout
    QVBoxLayout *pMainLayout = new QVBoxLayout;
    // Make the group tabs widget larger
    mpTabWidget->setMinimumHeight(200);
    mpTabWidget->setMinimumWidth(350);

    pMainLayout->addWidget(mpTabWidget);
    // Plot
    QHBoxLayout *pPlotLayout = new QHBoxLayout;
    pPlotLayout->addWidget(mpFxPlotLabel);
    pPlotLayout->addWidget(mpOpenPlotButton);
    pPlotLayout->addStretch();
    pMainLayout->addLayout(pPlotLayout);
    // stoptime
    QHBoxLayout *pStopTimeLayout = new QHBoxLayout;
    pStopTimeLayout->addWidget(mpStopTimeLabel);
    pStopTimeLayout->addWidget(mpStopTimeValue);
    pStopTimeLayout->addStretch();
    pMainLayout->addLayout(pStopTimeLayout);
    // Results folder path
    pMainLayout->addWidget(mpResultsFolderPathLabel);
    pMainLayout->addWidget(mpResultsFolderPathValue);

    // Accept button
    pMainLayout->addWidget(mpButtonBox);

    // Layout settings
    setLayout(pMainLayout);

    // Windows settings
    initializeWindowSettings();
}

void VectorialResultsDialog::initializeWindowSettings()
{
    setMinimumHeight(300);
    setMinimumWidth(450);
    setWindowTitle("Vectorial Analysis Results");
}

// Slots
void VectorialResultsDialog::openPlot()
{
    // Get path
    // Launch image viewer dialog
    ImageViewerDialog *pImageViewer = new ImageViewerDialog(mPlotPath,this);
    pImageViewer->show();
}
