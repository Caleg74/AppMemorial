TEMPLATE = app

QT += qml quick

CONFIG += c++11

SOURCES += src/main.cpp

RESOURCES += MGShowRanking.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = src/qml

QT_QUICK_CONTROLS_STYLE=Flat ./app

# Default rules for deployment.
include(deployment.pri)

OTHER_FILES += \
    ../MGCommon/qml-styles/StyleMGTabWidget.qml \
    ../MGCommon/qml-styles/StyleMGComboBox.qml \
    ../MGCommon/qml-styles/StyleMGTextInput.qml \
    ../MGCommon/qml-styles/StyleMGPushButton.qml \
    src/qml/MenRanking.qml \
    src/qml/MenRankingDelegate.qml \
    src/qml/TableTitleItem.qml \
    src/qml/main.qml
