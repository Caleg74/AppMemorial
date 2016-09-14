#include "coreapplication.h"
#include <QQmlContext>
#include "allroundmendatamodel.h"
#include "allroundwomendatamodel.h"
#include "allroundsortfilterproxymodel.h"
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

    // Men
    AllroundMenDataModel* pGymMenModel = AllroundMenDataModel::Instance();


    // Set filter
    m_qSortMProxy = new AllroundSortFilterProxyModel(this);
    m_qSortMProxy->setSortRole(AllroundMenDataModel::RankRole);
    m_qSortMProxy->setSourceModel(pGymMenModel);
    m_qSortMProxy->setDynamicSortFilter(true);

    ctxt->setContextProperty("AllroundMenDataModel", m_qSortMProxy); // Contains the filter, not the model

    // Women
    AllroundWomenDataModel* pGymWomenModel = AllroundWomenDataModel::Instance();

    // Set filter
    m_qSortWProxy = new AllroundSortFilterProxyModel(this);
    m_qSortWProxy->setSortRole(AllroundWomenDataModel::RankRole);
    m_qSortWProxy->setSourceModel(pGymWomenModel);
    m_qSortWProxy->setDynamicSortFilter(true);

    ctxt->setContextProperty("AllroundWomenDataModel", m_qSortWProxy); // Contains the filter, not the model

    // Timer for refreshing the scores automatically
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
    m_qSortMProxy->sort(0);

    AllroundWomenDataModel::Instance()->updateScores();
    m_qSortWProxy->sort(0);
}
