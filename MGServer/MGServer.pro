TEMPLATE = app

QT += sql qml quick widgets printsupport
CONFIG += c++11

SOURCES += \
    ../MGCommon/src/db/dbconnection.cpp \
    ../MGCommon/src/db/dbifacebase.cpp \
    ../MGCommon/src/cbbItems/comboboxmodel.cpp \
    ../MGCommon/src/cbbItems/countrylist.cpp \
    ../MGCommon/src/cbbItems/gymnastselectionlist.cpp \
    ../MGCommon/src/cbbItems/apparatusdata.cpp \
    ../MGCommon/src/cbbItems/apparatuslist.cpp \
    ../MGCommon/src/msgBox/messagebox.cpp \
    src/main.cpp \
    src/gymnastdata.cpp \
    src/gymnastdatamodel.cpp \
    src/gymnastselectdata.cpp \
    src/gymnastselectmodel.cpp \
    src/coreapplication.cpp \
    src/dbinterface.cpp \
    src/gymnastsortfilterproxymodel.cpp \
    src/saveforcescore.cpp \
    src/createpdf.cpp

HEADERS += \
    ../MGCommon/src/db/dbconnection.h \
    ../MGCommon/src/db/dbifacebase.cpp \
    ../MGCommon/src/cbbItems/comboboxmodel.h \
    ../MGCommon/src/cbbItems/countrylist.h \
    ../MGCommon/src/cbbItems/gymnastselectionlist.h \
    ../MGCommon/src/cbbItems/apparatusdata.h \
    ../MGCommon/src/cbbItems/apparatuslist.h \
    ../MGCommon/src/msgBox/messagebox.h \
    src/gymnastdata.h \
    src/gymnastdatamodel.h \
    src/gymnastselectdata.h \
    src/gymnastselectmodel.h \
    src/coreapplication.h \
    src/dbinterface.h \
    src/gymnastsortfilterproxymodel.h \
    src/saveforcescore.h \
    src/createpdf.h


INCLUDEPATH += \
    ../MGCommon/src/db \
    ../MGCommon/src/cbbItems \
    ../MGCommon/src/msgBox \
    src/

OTHER_FILES += \
    ../MGCommon/qml-styles/StyleMGTabWidget.qml \
    ../MGCommon/qml-styles/StyleMGComboBox.qml \
    ../MGCommon/qml-styles/StyleMGTextInput.qml \
    ../MGCommon/qml-styles/StyleMGPushButton.qml \
    ../MGCommon/qml-styles/StyleMGMsgBox.qml \
    src/qml/main.qml \
    src/qml/ForceScore.qml \
    src/qml/EventData.qml \
    src/qml/GymnastInfo.qml \
    src/qml/GymnastInfoDelegate.qml \
    src/qml/GymnastSelection.qml \
    src/qml/GymnastSelectionDelegate.qml


RESOURCES += MGServer.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = src/qml

# Default rules for deployment.
include(deployment.pri)
