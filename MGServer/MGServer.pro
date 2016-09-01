TEMPLATE = app

QT += sql qml quick widgets
CONFIG += c++11

SOURCES += \
    ../MGCommon/src/db/dbconnection.cpp \
    src/main.cpp \
    src/gymnastdata.cpp \
    src/gymnastdatamodel.cpp \
    src/coreapplication.cpp \
    src/comboboxmodel.cpp \
    src/countrylist.cpp \
    src/dbinterface.cpp

RESOURCES += MGServer.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = src/qml


# Default rules for deployment.
include(deployment.pri)

#DISTFILES += \
#    src/qml/GymnastData.qml

HEADERS += \
    ../MGCommon/src/db/dbconnection.h \
    src/gymnastdata.h \
    src/gymnastdatamodel.h \
    src/coreapplication.h \
    src/comboboxmodel.h \
    src/countrylist.h \
    src/dbinterface.h

INCLUDEPATH += \
    ../MGCommon/src/db

OTHER_FILES += \
    ../MGCommon/qml-styles/StyleMGTabWidget.qml \
    ../MGCommon/qml-styles/StyleMGComboBox.qml \
    ../MGCommon/qml-styles/StyleMGTextInput.qml \
    ../MGCommon/qml-styles/StyleMGPushButton.qml \
    src/qml/GymnastDelegate.qml \
    src/qml/GymnastInfo.qml \
    src/qml/main.qml \
    src/qml/Ranking.qml

DISTFILES += \
    src/qml/EventData.qml
