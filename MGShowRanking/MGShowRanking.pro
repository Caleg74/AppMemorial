TEMPLATE = app

QT += sql qml quick widgets

CONFIG += c++11

SOURCES += \
    ../MGCommon/src/cbbItems/apparatusdata.cpp \
    ../MGCommon/src/cbbItems/apparatuslist.cpp \
    ../MGCommon/src/db/dbconnection.cpp \
    ../MGCommon/src/cbbItems/comboboxmodel.cpp \
    ../MGCommon/src/cbbItems/countrylist.cpp \
    ../MGCommon/src/cbbItems/gymnastselectionlist.cpp \
    src/allroundmendata.cpp \
    src/allroundgymnastdatamodel.cpp \
    src/allroundmendatamodel.cpp \
    src/allroundsortfilterproxymodel.cpp \
    src/allroundwomendata.cpp \
    src/allroundwomendatamodel.cpp \
    src/coreapplication.cpp \
    src/dbinterface.cpp \
    src/main.cpp

HEADERS += \
    ../MGCommon/src/cbbItems/apparatusdata.h \
    ../MGCommon/src/cbbItems/apparatuslist.h \
    ../MGCommon/src/db/dbconnection.h \
    ../MGCommon/src/cbbItems/comboboxmodel.h \
    ../MGCommon/src/cbbItems/countrylist.h \
    ../MGCommon/src/cbbItems/gymnastselectionlist.h \
    src/allroundmendata.h \
    src/allroundgymnastdatamodel.h \
    src/allroundmendatamodel.h \
    src/allroundsortfilterproxymodel.h \
    src/allroundwomendata.h \
    src/allroundwomendatamodel.h \
    src/coreapplication.h \
    src/dbinterface.h

INCLUDEPATH += \
    ../MGCommon/src/db \
    ../MGCommon/src/cbbItems \
    src/

RESOURCES += MGShowRanking.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH = src/qml

QT_QUICK_CONTROLS_STYLE=Flat ./app

# Default rules for deployment.
include(deployment.pri)

OTHER_FILES += \
    ../MGCommon/qml-styles/StyleMGTabWidget.qml \
    ../MGCommon/qml-styles/StyleMGComboBox.qml \
    ../MGCommon/qml-styles/StyleMGTextInput.qml \
    ../MGCommon/qml-styles/StyleMGPushButton.qml \
    src/qml/AllroundMDelegate.qml \
    src/qml/AllroundWDelegate.qml \
    src/qml/MenRanking.qml \
    src/qml/WomenRanking.qml \
    src/qml/TableTitleItem.qml \
    src/qml/ApparatusScoreItem.qml \
    src/qml/TotalScoreItem.qml \
    src/qml/GymnastPosItem.qml \
    src/qml/main.qml
