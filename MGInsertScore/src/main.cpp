#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "coreapplication.h"
#include "apparatuslist.h"
#include "gymnasteventlist.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    CoreApplication cCoreApp;

    if (!cCoreApp.Init(engine))
    {
        qCritical() << "Initalization failed, application closed";
    }

    GymnastEventList::Instance()->Init(engine);
    engine.load(QUrl(QStringLiteral("qrc:qml/main.qml")));

    cCoreApp.Connect();   // connect all signals from the UI

//    QObject *topLevel = engine.rootObjects().value(0);
//    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
//    window->show();

    return app.exec();
    return 0;
} 
