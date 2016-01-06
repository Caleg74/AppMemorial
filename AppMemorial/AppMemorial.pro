TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += src/main.cpp

RESOURCES += memorial.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = src/qml


# Default rules for deployment.
include(deployment.pri)
