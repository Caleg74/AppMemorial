#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "CoreApplication.h"
#include "countrylist.h"
#include "gymnastselectionlist.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    CoreApplication cCoreApp;
    cCoreApp.Init(engine);

    CountryList cCountryList;
    cCountryList.Init(engine);

    GymnastSelectionList cGymnSelectList;
    cGymnSelectList.Init(engine);

    engine.load(QUrl(QStringLiteral("qrc:qml/main.qml")));

    cCoreApp.Connect();   // connect all signals from the UI

//    QObject *topLevel = engine.rootObjects().value(0);
//    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
//    window->show();

    return app.exec();
}

