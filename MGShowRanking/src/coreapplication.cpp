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
    AllroundMenDataModel* pGymModel = AllroundMenDataModel::Instance();

    QQmlContext *ctxt = p_qEngine.rootContext();

    // Set filter
    m_qSortProxy = new AllroundMenSortFilterProxyModel(this);
    m_qSortProxy->setSortRole(AllroundMenDataModel::FirstNameRole);
    m_qSortProxy->setSourceModel(pGymModel);
    m_qSortProxy->setDynamicSortFilter(true);

    ctxt->setContextProperty("AllroundMenDataModel", m_qSortProxy); // Contains the filter, not the model

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
