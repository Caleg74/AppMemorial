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
    GymnastDataModel* pGymModel = GymnastDataModel::Instance();
    GymnastSelectModel* pGymSelModel = GymnastSelectModel::Instance();

    QQmlContext *ctxt = p_qEngine.rootContext();

    // Set filter
    m_qSortProxy = new GymnastSortFilterProxyModel(this);
    m_qSortProxy->setSortRole(GymnastDataModel::FirstNameRole);
    m_qSortProxy->setSourceModel(pGymModel);
    m_qSortProxy->setDynamicSortFilter(true);

    ctxt->setContextProperty("GymnastDataModel", m_qSortProxy); // Contains the filter, not the model
    ctxt->setContextProperty("GymnastSelectModel", pGymSelModel);


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
    QQuickItem* qBtnSort = m_pAppEngine->rootObjects().first()->findChild<QQuickItem*>("btnSort");
    if (qBtnSort)
    {
        connect(qBtnSort, SIGNAL(clicked()), this, SLOT(onSortClicked()));
    }
}

void CoreApplication::onSortClicked()
{
    m_qSortProxy->sort(0);
}
