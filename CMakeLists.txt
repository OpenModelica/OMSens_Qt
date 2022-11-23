cmake_minimum_required (VERSION 3.14)

project(OMSens_Qt)

## This is used by the OpenModelica superproject. Pedantically, it should be done
## in OpenModelica itself but it is cleaner to set it here for now since this project
## is not used standalone.
## Anything installed from this directory and its subdirectories belongs
## to the install component 'omshell' if it is not explicitly changed.
set(CMAKE_INSTALL_DEFAULT_COMPONENT_NAME omsens)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)


set(OMSENS_QT_SOURCES dialogs/general/CSVViewerDialog.cpp
                    dialogs/general/ImageViewerDialog.cpp
                    dialogs/indiv/IndivParamSensAnalysisDialog.cpp
                    dialogs/indiv/IndivSensAnalTypeDialog.cpp
                    dialogs/indiv/IndivSensResultsDialog.cpp
                    dialogs/sweep/MultiParamSweepDialog.cpp
                    dialogs/sweep/SweepResultDialog.cpp
                    dialogs/vect/VectorialParamSensAnalysisDialog.cpp
                    dialogs/vect/VectorialResultsDialog.cpp
                    tabs/HelpTab.cpp
                    tabs/OptimizationTab.cpp
                    tabs/ParametersExtendedTab.cpp
                    tabs/ParametersSimpleTab.cpp
                    tabs/SensitivityMethodResultsTab.cpp
                    tabs/SimulationTab.cpp
                    tabs/VariablesTab.cpp
                    DualLists.cpp
                    main.cpp
                    OMSensDialog.cpp
                    tabs/optim_result/OptimizationResultParametersTab.cpp
                    tabs/optim_result/OptimizationResultOtherTab.cpp
                    tabs/sweep_result/SweepResultVariableTab.cpp
                    dialogs/help/HelpBrowser.cpp
                    tabs/PerturbationTab.cpp
                    specs/IndivSpecs.cpp
                    specs/SweepSpecs.cpp
                    specs/VectSpecs.cpp
                    OMSensPlugin.cpp
                    omedit_plugin/model.cpp)

set(OMSENS_QT_HEADERS dialogs/general/CSVViewerDialog.h
                    dialogs/general/ImageViewerDialog.h
                    dialogs/indiv/IndivParamSensAnalysisDialog.h
                    dialogs/indiv/IndivSensAnalTypeDialog.h
                    dialogs/indiv/IndivSensResultsDialog.h
                    dialogs/sweep/MultiParamSweepDialog.h
                    dialogs/sweep/SweepResultDialog.h
                    dialogs/vect/VectorialParamSensAnalysisDialog.h
                    dialogs/vect/VectorialResultsDialog.h
                    tabs/HelpTab.h
                    tabs/OptimizationTab.h
                    tabs/ParametersExtendedTab.h
                    tabs/ParametersSimpleTab.h
                    tabs/SensitivityMethodResultsTab.h
                    tabs/SimulationTab.h
                    tabs/VariablesTab.h
                    DualLists.h
                    OMSensDialog.h
                    TableItemDelegate.h
                    tabs/optim_result/OptimizationResultParametersTab.h
                    tabs/optim_result/OptimizationResultOtherTab.h
                    dialogs/BaseRunSpecsDialog.h
                    dialogs/BaseResultsDialog.h
                    tabs/sweep_result/SweepResultVariableTab.h
                    dialogs/help/HelpBrowser.h
                    tabs/PerturbationTab.h
                    ForceSignDoubleSpinbox.h
                    SciNotationDoubleSpinbox.h
                    specs/IndivSpecs.h
                    specs/RunSpecifications.h
                    specs/VectSpecs.h
                    OMSensPlugin.h
                    omedit_plugin/model.h)

add_library(omsensplugin SHARED ${OMSENS_QT_SOURCES} ${OMSENS_QT_HEADERS})

target_include_directories(omsensplugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(omsensplugin PUBLIC Qt5::Widgets)

install(TARGETS omsensplugin)
