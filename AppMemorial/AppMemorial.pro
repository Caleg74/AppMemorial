TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += src/main.cpp \
    src/gymnastdata.cpp \
    src/gymnastdatamodel.cpp \
    src/coreapplication.cpp \
    src/server/serverapp.cpp

RESOURCES += memorial.qrc

OTHER_FILES += src/qml/main.qml \
    src/qml/TabWidget.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = src/qml


# Default rules for deployment.
include(deployment.pri)

#DISTFILES += \
#    src/qml/GymnastData.qml

HEADERS += \
    src/gymnastdata.h \
    src/gymnastdatamodel.h \
    src/coreapplication.h \
    src/server/serverapp.h

INCLUDEPATH += src/server

DISTFILES += \
    src/qml/GymnastInfo.qml \
    src/qml/StyleMGComboBox.qml \
    src/qml/StyleMGTextInput.qml \
    src/qml/GymnastDelegate.qml

DEFINES += SERVER
