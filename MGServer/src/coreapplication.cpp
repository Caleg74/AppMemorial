#include "coreapplication.h"
#include <QQmlContext>
#include "gymnastdatamodel.h"
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
    if (!dbInterface::Instance()->loadDriver())
    {
//            QMessageBox::question(NULL, QString("Test"), QString("Quit?"), QMessageBox::Close);
    }

    // initialize the database
    QSqlError err = dbInterface::Instance()->initDb();
    if (err.type() != QSqlError::NoError)
    {
        return;
    }

    // save it as a class member
    m_pAppEngine = &p_qEngine;
    GymnastDataModel* pGymModel = GymnastDataModel::Instance();

    QQmlContext *ctxt = p_qEngine.rootContext();
//    m_qProxyModel = new FilterData(this);

//    m_qProxyModel->setFilterRole(GymnastDataModel::SignalSection);
//    m_qProxyModel->setFilterRegExp("0");    // enum value of "SignalDoor"
    ctxt->setContextProperty("GymnastDataModel", pGymModel);

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
