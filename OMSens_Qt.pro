#-------------------------------------------------
#
# Project created by QtCreator 2018-10-04T10:55:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Vars if standalone app
# TARGET = OMSens_Qt
# TEMPLATE = app
# Vars if plugin
TEMPLATE        = lib
TARGET          = $$qtLibraryTarget(omsensplugin)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    dialogs/general/CSVViewerDialog.cpp \
    dialogs/general/ImageViewerDialog.cpp \
    dialogs/indiv/IndivParamSensAnalysisDialog.cpp \
    dialogs/indiv/IndivSensAnalTypeDialog.cpp \
    dialogs/indiv/IndivSensResultsDialog.cpp \
    dialogs/sweep/MultiParamSweepDialog.cpp \
    dialogs/sweep/SweepResultDialog.cpp \
    dialogs/vect/VectorialParamSensAnalysisDialog.cpp \
    dialogs/vect/VectorialResultsDialog.cpp \
    tabs/HelpTab.cpp \
    tabs/OptimizationTab.cpp \
    tabs/ParametersExtendedTab.cpp \
    tabs/ParametersSimpleTab.cpp \
    tabs/SensitivityMethodResultsTab.cpp \
    tabs/SimulationTab.cpp \
    tabs/VariablesTab.cpp \
    DualLists.cpp \
    main.cpp \
    OMSensDialog.cpp \
    tabs/optim_result/OptimizationResultParametersTab.cpp \
    tabs/optim_result/OptimizationResultOtherTab.cpp \
    tabs/sweep_result/SweepResultVariableTab.cpp \
    dialogs/help/HelpBrowser.cpp \
    tabs/PerturbationTab.cpp \
    specs/IndivSpecs.cpp \
    specs/SweepSpecs.cpp \
    specs/VectSpecs.cpp \
    OMSensPlugin.cpp \
    omedit_plugin/model.cpp \
    dialogs/functions/HistogramCreator.cpp \
    dialogs/PlotsDialog.cpp \
    dialogs/sweep/PlotFromDataDialog.cpp \
    helpers/CSVReader.cpp \
    dialogs/functions/ScatterPlotCreator.cpp \
    specs/ConstrainedIntervalSpecs.cpp \
    dialogs/constrained/ConstrainedIntervalSensAnalysisDialog.cpp \
    tabs/ParameterCombinationRunMap.cpp \
    dialogs/functions/LinesPlotVisualizer.cpp \
    tabs/PlotOptimizationTab.cpp \
    tabs/PlotSweepTab.cpp

HEADERS += \
    dialogs/general/CSVViewerDialog.h \
    dialogs/general/ImageViewerDialog.h \
    dialogs/indiv/IndivParamSensAnalysisDialog.h \
    dialogs/indiv/IndivSensAnalTypeDialog.h \
    dialogs/indiv/IndivSensResultsDialog.h \
    dialogs/sweep/MultiParamSweepDialog.h \
    dialogs/sweep/SweepResultDialog.h \
    dialogs/vect/VectorialParamSensAnalysisDialog.h \
    dialogs/vect/VectorialResultsDialog.h \
    tabs/HelpTab.h \
    tabs/OptimizationTab.h \
    tabs/ParametersExtendedTab.h \
    tabs/ParametersSimpleTab.h \
    tabs/SensitivityMethodResultsTab.h \
    tabs/SimulationTab.h \
    tabs/VariablesTab.h \
    DualLists.h \
    OMSensDialog.h \
    TableItemDelegate.h \
    tabs/optim_result/OptimizationResultParametersTab.h \
    tabs/optim_result/OptimizationResultOtherTab.h \
    dialogs/BaseRunSpecsDialog.h \
    dialogs/BaseResultsDialog.h \
    tabs/sweep_result/SweepResultVariableTab.h \
    dialogs/help/HelpBrowser.h \
    tabs/PerturbationTab.h \
    ForceSignDoubleSpinbox.h \
    SciNotationDoubleSpinbox.h \
    specs/IndivSpecs.h \
    specs/RunSpecifications.h \
    specs/VectSpecs.h \
    OMSensPlugin.h \
    omedit_plugin/interfaces.h \
    omedit_plugin/model.h \
    dialogs/functions/HistogramCreator.h \
    dialogs/PlotsDialog.h \
    dialogs/sweep/PlotFromDataDialog.h \
    helpers/CSVReader.h \
    dialogs/functions/ScatterPlotCreator.h \
    specs/ConstrainedIntervalSpecs.h \
    dialogs/constrained/ConstrainedIntervalSensAnalysisDialog.h \
    tabs/ParameterCombinationRunMap.h \
    dialogs/functions/LinesPlotVisualizer.h \
    tabs/PlotOptimizationTab.h \
    tabs/PlotSweepTab.h

DISTFILES += \
    resource/ModelWithVariousParams.mo \
    dialogs/indiv/help.html \
    dialogs/sweep/help.html \
    dialogs/vect/help.html \
    resource/help/help.html

RESOURCES += \
    resources.qrc
