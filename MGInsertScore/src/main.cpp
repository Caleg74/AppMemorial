#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "coreapplication.h"
#include "apparatuslist.h"
#include "gymnastselectionlist.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    CoreApplication cCoreApp;
    cCoreApp.Init(engine);

    GymnastSelectionList::Instance()->Init(engine);
    ApparatusList::Instance()->Init(engine);

    engine.load(QUrl(QStringLiteral("qrc:qml/main.qml")));

    cCoreApp.Connect();   // connect all signals from the UI

//    QObject *topLevel = engine.rootObjects().value(0);
//    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
//    window->show();

    return app.exec();
}
