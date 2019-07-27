#include "PlotFromDataDialog.h"
#include "../functions/HistogramCreator.h"
#include <QProcess>
#include <QDialog>
#include <QDateTime>
#include <QProgressDialog>
#include <QWidget>
#include <QJsonObject>
#include <QFormLayout>
#include <QPushButton>

PlotFromDataDialog::PlotFromDataDialog(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *pParent) : BaseResultsDialog(pParent)
{
    plot_mPythonBinPath     = mPythonBinPath;
    plot_mOMSensPath        = mOMSensPath;
    plot_mOMSensResultsPath = mOMSensResultsPath + "sweep_results/";

    // Dialog settings
    setMinimumWidth(410);
    setWindowTitle("Multiparameter Sweep Plots");

    // TODO: seleccionar experimento especifico
    // TODO: dar opciones de parametros sobre los cuales hacer el histograma (van a depender de cada experimento)

    // Choose type of plot (Histogram, etc.)
    QDialogButtonBox *histogramButtonBox = new QDialogButtonBox;
    histogramButtonBox->addButton("Histogram", QDialogButtonBox::AcceptRole);
    connect(histogramButtonBox, &QDialogButtonBox::accepted, this, &PlotFromDataDialog::openHistogramDialog);

    QDialogButtonBox *scatterButtonBox = new QDialogButtonBox;
    scatterButtonBox->addButton("Scatter plot", QDialogButtonBox::AcceptRole);

    // Layout
    QVBoxLayout *pMainLayout = new QVBoxLayout;
    pMainLayout->addWidget(histogramButtonBox, 0, Qt::AlignLeft);
    pMainLayout->addWidget(scatterButtonBox, 0, Qt::AlignLeft);

    // Initialize layouts
    setLayout(pMainLayout);
}

int PlotFromDataDialog::openHistogramDialog()
{
    // TODO: pasar el el results folder que se haya seleccionado con los widgets (NO HARCODEAR!)
    HistogramCreator *h = new HistogramCreator(plot_mPythonBinPath,
                                               plot_mOMSensPath,
                                               plot_mOMSensResultsPath + "2019-07-26/8_8_3/results/", this);
    h->show();
}

int PlotFromDataDialog::openScatterplotDialog()
{

}










