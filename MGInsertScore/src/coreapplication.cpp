#include "coreapplication.h"
#include <QQmlContext>
#include "dbinterface.h"


CoreApplication::CoreApplication(QObject *parent)
    : QObject(parent)
    , m_pAppEngine(NULL)
{

}

CoreApplication::~CoreApplication()
{

}

void CoreApplication::Init(QQmlApplicationEngine& p_qEngine)
{
    if (dbInterface::Instance()->loadDriver())
    {
        qInfo() << "QOBCD driver loaded successfully";
    }
    else
    {
        return;
    }

    // initialize the database
    if (!dbInterface::Instance()->initDb())
    {
        return;
    }

    // save it as a class member
    m_pAppEngine = &p_qEngine;

    QQmlContext *ctxt = p_qEngine.rootContext();
//    m_qProxyModel = new FilterData(this);

//    m_qProxyModel->setFilterRole(GymnastDataModel::SignalSection);
//    m_qProxyModel->setFilterRegExp("0");    // enum value of "SignalDoor"
//    connect(pGymModel, SIGNAL(OutputChanged(unsigned int)),
//            &m_cIoWrap, SLOT(SetOutput(unsigned int)));
}

void CoreApplication::Connect()
{

    // Add gymnast button (TODO move toserver app)
//    QObject* addGymnatBtn = m_pAppEngine->rootObjects().first()->findChild<QObject*>("btnAddGymnast");
//    if (addGymnatBtn)
//    {
//        connect(addGymnatBtn, SIGNAL(addGymnast(QString firstName, QString lastName, QString country, QString sex)),
//                GymnastDataModel::Instance(), SLOT(AddGymnast(QString firstName, QString lastName, QString country, QString sex)));
//    }

}
