TEMPLATE = app

QT += sql qml quick widgets

CONFIG += c++11

SOURCES += \
    ../MGCommon/src/cbbItems/apparatusdata.cpp \
    ../MGCommon/src/cbbItems/apparatuslist.cpp \
    ../MGCommon/src/db/dbconnection.cpp \
    ../MGCommon/src/db/dbifacebase.cpp \
    ../MGCommon/src/cbbItems/comboboxmodel.cpp \
    ../MGCommon/src/cbbItems/countrylist.cpp \
    ../MGCommon/src/cbbItems/gymnastselectionlist.cpp \
    src/allroundmendata.cpp \
    src/gymnastdatamodel.cpp \
    src/allroundmendatamodel.cpp \
    src/sortfilterproxymodel.cpp \
    src/allroundwomendata.cpp \
    src/allroundwomendatamodel.cpp \
    src/singlemwdata.cpp \
    src/singlemwdatamodel.cpp \
    src/coreapplication.cpp \
    src/dbinterface.cpp \
    src/main.cpp

HEADERS += \
    ../MGCommon/src/cbbItems/apparatusdata.h \
    ../MGCommon/src/cbbItems/apparatuslist.h \
    ../MGCommon/src/db/dbconnection.h \
    ../MGCommon/src/db/dbifacebase.h \
    ../MGCommon/src/cbbItems/comboboxmodel.h \
    ../MGCommon/src/cbbItems/countrylist.h \
    ../MGCommon/src/cbbItems/gymnastselectionlist.h \
    src/allroundmendata.h \
    src/gymnastdatamodel.h \
    src/allroundmendatamodel.h \
    src/sortfilterproxymodel.h \
    src/allroundwomendata.h \
    src/allroundwomendatamodel.h \
    src/singlemwdata.h \
    src/singlemwdatamodel.h \
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
    src/qml/SingleMWDelegate.qml \
    src/qml/MenRanking.qml \
    src/qml/WomenRanking.qml \
    src/qml/ApparatusRanking.qml \
    src/qml/ApparatusRankingM.qml \
    src/qml/ApparatusRankingW.qml \
    src/qml/TableTitleItem.qml \
    src/qml/ScoreItem.qml \
    src/qml/GymnastPosItem.qml \
    src/qml/main.qml
