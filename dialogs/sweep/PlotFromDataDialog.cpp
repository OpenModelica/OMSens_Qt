#include "PlotFromDataDialog.h"
#include "dialogs/PlotsDialog.h"
#include <QProcess>
#include <QDialog>
#include <QDateTime>
#include <QProgressDialog>
#include <QWidget>
#include <QJsonObject>
#include <QFormLayout>
#include <QPushButton>
#include <QFileDialog>

void PlotFromDataDialog::setSpecificExperiment()
{

    // Launch dialog
    QString path = QFileDialog::getExistingDirectory(this, tr("Choose Specific experiment results folder"),
                                                 plot_mOMSensResultsPath,
                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!path.isEmpty() && !path.isNull())
    {
        // Save path into member variable
        plot_specific_experiment = path;
        plot_specific_experiment_label->setText(plot_specific_experiment);
    }
}

PlotFromDataDialog::PlotFromDataDialog(QString mPythonBinPath, QString mOMSensPath, QString mOMSensResultsPath, QWidget *pParent) : BaseResultsDialog(pParent)
{
    plot_mPythonBinPath      = mPythonBinPath;
    plot_mOMSensPath         = mOMSensPath;
    plot_mOMSensResultsPath  = mOMSensResultsPath + "sweep_results/";
    plot_specific_experiment = "";

    // Dialog settings
    setMinimumWidth(410);
    setWindowTitle("Multiparameter Sweep Plots");

    // TODO: seleccionar experimento especifico
    QLabel *plot_specific_experiment_title = new QLabel("Choose experiment's directory:");

    plot_specific_experiment_label = new QLabel(plot_specific_experiment);
    plot_specific_experiment_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    plot_specific_experiment_label_browse_button = new QPushButton("Browse");
    plot_specific_experiment_label_browse_button->setAutoDefault(true);
    plot_specific_experiment_label_browse_button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(plot_specific_experiment_label_browse_button, SIGNAL(clicked()), this, SLOT(setSpecificExperiment()));

    // Choose type of plot (Histogram, etc.)
    QDialogButtonBox *plotsDialogButtonBox = new QDialogButtonBox;
    plotsDialogButtonBox->addButton("Plots analysis (multi-tab)", QDialogButtonBox::AcceptRole);
    connect(plotsDialogButtonBox, &QDialogButtonBox::accepted, this, &PlotFromDataDialog::openPlotsDialog);

    // Layout
    QVBoxLayout *pMainLayout = new QVBoxLayout;

    // Set specific experiment
    pMainLayout->addWidget(plot_specific_experiment_title, 0, Qt::AlignLeft);
    QHBoxLayout *set_specific_experiment_layout = new QHBoxLayout;
    set_specific_experiment_layout->addWidget(plot_specific_experiment_label);
    set_specific_experiment_layout->addWidget(plot_specific_experiment_label_browse_button);
    pMainLayout->addLayout(set_specific_experiment_layout);

    // Choose type of plot
    pMainLayout->addWidget(plotsDialogButtonBox, 0, Qt::AlignLeft);

    // Initialize layouts
    setLayout(pMainLayout);
}

void PlotFromDataDialog::openPlotsDialog()
{
    // TODO: raise warning if plot_specific_experiment == ""
    if(plot_specific_experiment != "") {
        PlotsDialog *p = new PlotsDialog(plot_mPythonBinPath,
                                         plot_mOMSensPath,
                                         plot_specific_experiment,
                                         this);
        p->show();
    }
}










