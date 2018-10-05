# This file specifies what components of the project should be used when imported as a plugin

HEADERS +=  $$PWD/dialogs/general/CSVViewerDialog.h \
    $$PWD/dialogs/general/ImageViewerDialog.h \
    $$PWD/dialogs/indiv/IndivParamSensAnalysisDialog.h \
    $$PWD/dialogs/indiv/IndivSensAnalTypeDialog.h \
    $$PWD/dialogs/indiv/IndivSensResultsDialog.h \
    $$PWD/dialogs/sweep/MultiParamSweepDialog.h \
    $$PWD/dialogs/sweep/SweepResultDialog.h \
    $$PWD/dialogs/vect/VectorialParamSensAnalysisDialog.h \
    $$PWD/dialogs/vect/VectorialResultsDialog.h \
    $$PWD/tabs/HelpTab.h \
    $$PWD/tabs/OptimizationTab.h \
    $$PWD/tabs/ParametersExtendedTab.h \
    $$PWD/tabs/ParametersSimpleTab.h \
    $$PWD/tabs/SensitivityMethodResultsTab.h \
    $$PWD/tabs/SimulationTab.h \
    $$PWD/tabs/VariablesTab.h \
    $$PWD/DualLists.h \
    $$PWD/model.h \
    $$PWD/OMSensDialog.h \
    $$PWD/TableItemDelegate.h
SOURCES +=  $$PWD/dialogs/general/CSVViewerDialog.cpp \
    $$PWD/dialogs/general/ImageViewerDialog.cpp \
    $$PWD/dialogs/indiv/IndivParamSensAnalysisDialog.cpp \
    $$PWD/dialogs/indiv/IndivSensAnalTypeDialog.cpp \
    $$PWD/dialogs/indiv/IndivSensResultsDialog.cpp \
    $$PWD/dialogs/sweep/MultiParamSweepDialog.cpp \
    $$PWD/dialogs/sweep/SweepResultDialog.cpp \
    $$PWD/dialogs/vect/VectorialParamSensAnalysisDialog.cpp \
    $$PWD/dialogs/vect/VectorialResultsDialog.cpp \
    $$PWD/tabs/HelpTab.cpp \
    $$PWD/tabs/OptimizationTab.cpp \
    $$PWD/tabs/ParametersExtendedTab.cpp \
    $$PWD/tabs/ParametersSimpleTab.cpp \
    $$PWD/tabs/SensitivityMethodResultsTab.cpp \
    $$PWD/tabs/SimulationTab.cpp \
    $$PWD/tabs/VariablesTab.cpp \
    $$PWD/DualLists.cpp \
    $$PWD/model.cpp \
    $$PWD/OMSensDialog.cpp

RESOURCES += \
    $$PWD/resources.qrc
