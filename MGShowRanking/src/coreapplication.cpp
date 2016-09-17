#include "coreapplication.h"
#include <QQmlContext>
#include "sortfilterproxymodel.h"
#include "dbinterface.h"
#include <QQuickItem>
#include <QDebug>

CoreApplication::CoreApplication(QObject *parent)
    : QObject(parent)
    , m_pGymWomenModel(NULL)
    , m_pGymMenModel(NULL)
    , m_pSingleMModel(NULL)
    , m_pSingleWModel(NULL)
    , m_pAppEngine(NULL)
    , m_qSortMProxy(NULL)
    , m_qSortWProxy(NULL)
    , m_qSortSingleMProxy(NULL)
    , m_qSortSingleWProxy(NULL)
    , m_updateTimer(NULL)
{

}

CoreApplication::~CoreApplication()
{
    delete m_pGymWomenModel;
    delete m_pGymMenModel;
    delete m_pSingleMModel;
    delete m_pSingleWModel;
    delete m_qSortMProxy;
    delete m_qSortWProxy;
    delete m_updateTimer;
    delete m_qSortSingleMProxy;
    delete m_qSortSingleWProxy;
    m_pGymWomenModel = 0;
    m_pGymMenModel = 0;
    m_pSingleMModel = 0;
    m_pSingleWModel = 0;
    m_qSortMProxy = 0;
    m_qSortWProxy = 0;
    m_updateTimer = 0;
    m_qSortSingleMProxy = 0;
    m_qSortSingleWProxy = 0;
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
    ApparatusList::Instance()->Init(p_qEngine, "apparatusModelM", &m_cbbApparatusMen);
    ApparatusList::Instance()->FillComboList(&m_cbbApparatusMen, "M", false);

    m_pGymMenModel = new AllroundMenDataModel();

    // Set filter
    m_qSortMProxy = new SortFilterProxyModel(this);
    m_qSortMProxy->setSortRole(AllroundMenDataModel::RankRole);
    m_qSortMProxy->setSourceModel(m_pGymMenModel);
    m_qSortMProxy->setDynamicSortFilter(true);

    ctxt->setContextProperty("AllroundMenDataModel", m_qSortMProxy); // Contains the filter, not the model
    m_qSortMProxy->sort(0);

    // Women
    m_pGymWomenModel =  new AllroundWomenDataModel();

    // Set filter
    ApparatusList::Instance()->Init(p_qEngine, "apparatusModelW", &m_cbbApparatusWomen);
    ApparatusList::Instance()->FillComboList(&m_cbbApparatusWomen, "F", false);

    m_qSortWProxy = new SortFilterProxyModel(this);
    m_qSortWProxy->setSortRole(AllroundWomenDataModel::RankRole);
    m_qSortWProxy->setSourceModel(m_pGymWomenModel);
    m_qSortWProxy->setDynamicSortFilter(true);

    ctxt->setContextProperty("AllroundWomenDataModel", m_qSortWProxy); // Contains the filter, not the model
    m_qSortWProxy->sort(0);

    // Single Men model
    m_pSingleMModel = new SingleMWDataModel("M");

    // Set filter
    m_qSortSingleMProxy = new SortFilterProxyModel(this);
    m_qSortSingleMProxy->setSortRole(SingleMWDataModel::RankRole);
    m_qSortSingleMProxy->setFilterRole(SingleMWDataModel::FinalScoreSingleMW);
    m_qSortSingleMProxy->setSourceModel(m_pSingleMModel);
    m_qSortSingleMProxy->setDynamicSortFilter(true);

    ctxt->setContextProperty("SingleMDataModel", m_qSortSingleMProxy); // Contains the filter, not the model
    m_qSortSingleMProxy->sort(0);
//    // Timer for refreshing the scores automatically


//    connect(pGymModel, SIGNAL(OutputChanged(unsigned int)),
//            &m_cIoWrap, SLOT(SetOutput(unsigned int)));
}

void CoreApplication::Connect()
{
    QObject *topLevel = m_pAppEngine->rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    if (window)
    {
        connect(topLevel, SIGNAL(afterRendering()), this, SLOT(onWindowLoaded()));
        connect(topLevel, SIGNAL(closing(QQuickCloseEvent*)), this, SLOT(onWindowClosing(QQuickCloseEvent*)));
    }

    QQuickItem* cbbApparatusMen = m_pAppEngine->rootObjects().first()->findChild<QQuickItem*>("cbbAppartusM");
    if (cbbApparatusMen)
    {
        connect(cbbApparatusMen, SIGNAL(selectedTextChanged(QString)),
                this, SLOT(onApparatusMChanged(QString)));

    }
}
void CoreApplication::onWindowLoaded()
{
    if (m_updateTimer == NULL)
    {
        m_updateTimer = new QTimer();
        connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(updateScores()));
        m_updateTimer->start(2000); //time specified in ms
    }
}

void CoreApplication::onWindowClosing(QQuickCloseEvent* p_event)
{
    qDebug() << "onWindowClosing()";
    if (m_updateTimer != NULL)
    {
        m_updateTimer->stop();
        m_updateTimer->disconnect();    // disconnect all signals
    }
}

void CoreApplication::updateScores()
{
        m_pGymMenModel->updateScores();
        m_qSortMProxy->sort(0, Qt::AscendingOrder);

        m_pGymWomenModel->updateScores();
        m_qSortWProxy->sort(0, Qt::AscendingOrder);

        m_pSingleMModel->updateScores();
        m_qSortSingleMProxy->sort(0, Qt::AscendingOrder);
}

void CoreApplication::onApparatusMChanged(QString p_currentTxt)
{
    if (p_currentTxt != "Attrezzo..")
    {
        // set Title
        QObject* ttiApparatusMen = m_pAppEngine->rootObjects().first()->findChild<QObject*>("singleApparatusMId");
        if (ttiApparatusMen)
        {

            // only exception
            if (p_currentTxt == "Cavallo a maniglie")
                p_currentTxt = "Cavallo a\nmaniglie"; // split into 2 lines

            ttiApparatusMen->setProperty("text", p_currentTxt);

            QString strImageFile = "/images/";
            ApparatusList::EApparatusMen eApparatusM;

            if      (p_currentTxt.compare("Suolo") ==  0) { strImageFile += "Floor.svg"; eApparatusM = ApparatusList::AMFloor; }
            else if (p_currentTxt.compare("Cavallo a maniglie") == 0) { strImageFile += "PommelHorse.svg"; eApparatusM = ApparatusList::AMPommelHores; }
            else if (p_currentTxt.compare("Anelli") ==  0) { strImageFile += "Rings.svg"; eApparatusM = ApparatusList::AMRings; }
            else if (p_currentTxt.compare("Volteggio") ==  0) { strImageFile += "Vault.svg"; eApparatusM = ApparatusList::AMVault; }
            else if (p_currentTxt.compare("Parallele") ==  0) { strImageFile += "ParallelBars.svg"; eApparatusM = ApparatusList::AMParallelBars; }
            else if (p_currentTxt.compare("Sbarra") ==  0) { strImageFile += "HorizontalBar.svg"; eApparatusM = ApparatusList::AMHorizontalBar; }
            else
            {
                strImageFile += "Empty.svg";
                qCritical() << "Wrong apparatus selected";
                return; // ?
            }

            // set image
            ttiApparatusMen->setProperty("imageSource", strImageFile);

            // Retrieve scores for the selected floor
            m_pSingleMModel->setApparatus(eApparatusM);
            m_pSingleMModel->updateScores();
        }

//        int iAthleteId = dbInterface::Instance()->getGymnastId(firstName, lastName);
//        QString strGender = dbInterface::Instance()->getGender(iAthleteId);

//        ApparatusList::Instance()->FillComboList(&m_pApparatusCbbModel, strGender);
    }
 }
