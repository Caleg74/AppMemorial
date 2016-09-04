TEMPLATE = app

QT += sql qml quick widgets
CONFIG += c++11

SOURCES += \
    ../MGCommon/src/db/dbconnection.cpp \
    src/main.cpp \
    src/gymnastdata.cpp \
    src/gymnastdatamodel.cpp \
    src/gymnastselectdata.cpp \
    src/gymnastselectmodel.cpp \
    src/coreapplication.cpp \
    src/cbbItems/comboboxmodel.cpp \
    src/cbbItems/countrylist.cpp \
    src/cbbItems/gymnastselectionlist.cpp \
    src/dbinterface.cpp

HEADERS += \
    ../MGCommon/src/db/dbconnection.h \
    src/gymnastdata.h \
    src/gymnastdatamodel.h \
    src/gymnastselectdata.h \
    src/gymnastselectmodel.h \
    src/coreapplication.h \
    src/cbbItems/comboboxmodel.h \
    src/cbbItems/countrylist.h \
    src/cbbItems/gymnastselectionlist.h \
    src/dbinterface.h

INCLUDEPATH += \
    ../MGCommon/src/db \
    src/cbbItems \
    src/

OTHER_FILES += \
    ../MGCommon/qml-styles/StyleMGTabWidget.qml \
    ../MGCommon/qml-styles/StyleMGComboBox.qml \
    ../MGCommon/qml-styles/StyleMGTextInput.qml \
    ../MGCommon/qml-styles/StyleMGPushButton.qml \
    src/qml/main.qml \
    src/qml/Ranking.qml \
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
