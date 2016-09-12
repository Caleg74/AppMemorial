#include "coreapplication.h"
#include <QQmlContext>
#include "allroundmendatamodel.h"
#include "allroundmensortfilterproxymodel.h"
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
    AllroundMenDataModel* pGymMenModel = AllroundMenDataModel::Instance();

    QQmlContext *ctxt = p_qEngine.rootContext();

    // Set filter
    m_qSortProxy = new AllroundMenSortFilterProxyModel(this);
    m_qSortProxy->setSortRole(AllroundMenDataModel::RankRole);
    m_qSortProxy->setSourceModel(pGymMenModel);
    m_qSortProxy->setDynamicSortFilter(true);

    ctxt->setContextProperty("AllroundMenDataModel", m_qSortProxy); // Contains the filter, not the model

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScores()));
    timer->start(2000); //time specified in ms

//    connect(pGymModel, SIGNAL(OutputChanged(unsigned int)),
//            &m_cIoWrap, SLOT(SetOutput(unsigned int)));
}

void CoreApplication::Connect()
{

//    QQuickItem* qBtnSort = m_pAppEngine->rootObjects().first()->findChild<QQuickItem*>("btnSort");
//    if (qBtnSort)
//    {
//        connect(qBtnSort, SIGNAL(clicked()), this, SLOT(onSortClicked()));
//    }
}

void CoreApplication::updateScores()
{
    AllroundMenDataModel::Instance()->updateScores();
    m_qSortProxy->sort(0);
}
