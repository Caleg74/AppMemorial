#include "coreapplication.h"
#include <QQmlContext>
#include "gymnastdatamodel.h"
#include "gymnastselectmodel.h"
#include "dbinterface.h"
#include <QQuickItem>
#include "apparatuslist.h"
#include "messagebox.h"
#include "saveforcescore.h"

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

    ApparatusList::Instance()->Init(p_qEngine, "apparatusModel", &m_pApparatusCbbModel);
    MessageBox::SetEngine(m_pAppEngine);

//    connect(pGymModel, SIGNAL(OutputChanged(unsigned int)),
//            &m_cIoWrap, SLOT(SetOutput(unsigned int)));
}

void CoreApplication::Connect()
{
    QObject* saveScoreBtn = m_pAppEngine->rootObjects().first()->findChild<QObject*>("btnSaveScore");
    if (saveScoreBtn)
    {
        connect(saveScoreBtn, SIGNAL(saveScore(QString, QString, QString, QString)),
                SaveForceScore::Instance(), SLOT(onSaveScore(QString, QString, QString, QString)));
    }

    QQuickItem* cbbGymnast = m_pAppEngine->rootObjects().first()->findChild<QQuickItem*>("cbbGymnastSelection");
    if (cbbGymnast)
    {
        connect(cbbGymnast, SIGNAL(selectedTextChanged(QString)),
                this, SLOT(onGymnastChanged(QString)));
    }
}

void CoreApplication::onGymnastChanged(QString p_currentTxt)
{
    if (p_currentTxt != "Seleziona ginnasti..")
    {
        QStringList strSplit = p_currentTxt.split(',');
        if (strSplit.count() < 2)
        {
            qDebug() << "onGymnastChanged(): first/last name formatting error";
        }
        QString firstName = strSplit.at(0).trimmed();
        QString lastName =  strSplit.at(1).trimmed();

        if (!firstName.isEmpty() && !lastName.isEmpty())
        {
            int iAthleteId = dbInterface::Instance()->getGymnastId(firstName, lastName);
            QString strGender = dbInterface::Instance()->getGender(iAthleteId);

            ApparatusList::Instance()->FillComboList(&m_pApparatusCbbModel, strGender);
        }
        else
        {
            qDebug() << "onGymnastChanged(): first/last name is empty";
        }
    }
}
