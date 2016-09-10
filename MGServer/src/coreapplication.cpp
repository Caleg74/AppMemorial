#include "coreapplication.h"
#include <QQmlContext>
#include "gymnastdatamodel.h"
#include "gymnastselectmodel.h"
#include "dbinterface.h"
#include <QQuickItem>

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

    // Create the the model for the gymnasts of every event
    GymnastDataModel* pGymModel = GymnastDataModel::Instance();
    // Set filter
    m_qSortProxyGymnast = new GymnastSortFilterProxyModel(this);
    m_qSortProxyGymnast->setSortRole(GymnastDataModel::FirstNameRole);
    m_qSortProxyGymnast->setSourceModel(pGymModel);
    m_qSortProxyGymnast->setDynamicSortFilter(true);
    ctxt->setContextProperty("GymnastDataModel", m_qSortProxyGymnast); // Contains the filter, not the model
    m_qSortProxyGymnast->sort(0);

    // Create the "registers to this event gymnasts" model
    GymnastSelectModel* pGymSelModel = GymnastSelectModel::Instance();
    // Set filter
    m_qSortProxySelectedGymnast = new GymnastSortFilterProxyModel(this);
    m_qSortProxySelectedGymnast->setSortRole(GymnastDataModel::FirstNameRole);
    m_qSortProxySelectedGymnast->setSourceModel(pGymSelModel);
    m_qSortProxySelectedGymnast->setDynamicSortFilter(true);
    ctxt->setContextProperty("GymnastSelectModel", m_qSortProxySelectedGymnast);
    m_qSortProxySelectedGymnast->sort(0);

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

