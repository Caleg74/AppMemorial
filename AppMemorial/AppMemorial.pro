TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += src/main.cpp \
    src/gymnastdata.cpp \
    src/gymnastdatamodel.cpp

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
    src/gymnastdatamodel.h

DISTFILES += \
    src/qml/GymnastInfo.qml
