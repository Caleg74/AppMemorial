#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QDebug>
#include "coreapplication.h"
#include "apparatuslist.h"
#include <signal.h>
#include <cstdlib>

void signalHandler(int signal);

int main(int argc, char ** argv)
{

    // Handling OS signals
#ifdef _WIN32
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGABRT, signalHandler);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    CoreApplication cCoreApp;
    cCoreApp.Init(engine);

    engine.load(QUrl(QStringLiteral("qrc:qml/main.qml")));

    cCoreApp.Connect();   // connect all signals from the UI


    return app.exec();

}

void signalHandler(int signal)
{

  switch(signal) {

  case SIGINT:    qDebug() << "Application: interrupted"; break;
//  case SIGKILL:   qDebug() << "Application: killed\n"; break;
//  case SIGQUIT:   qDebug() << "Application: quit\n"; break;
//  case SIGSTOP:   qDebug() << "Application: stopped\n"; break;
  case SIGTERM:   qDebug() << "Application: terminated\n"; break;
  case SIGABRT:   qDebug() << "Application aborted\n"; break;

  //case SIGSEGV:   qDebug() << "Application: segmentation fault\n"; break;
  default:        qDebug() << "Application: application exiting\n"; break;

  }

  QCoreApplication::quit();
}
