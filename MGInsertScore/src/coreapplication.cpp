#include "coreapplication.h"
#include <QQmlContext>
#include "dbinterface.h"
#include "savescore.h"
#include "messagebox.h"
#include <qquickitem.h>
#include "apparatuslist.h"


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

    ApparatusList::Instance()->Init(p_qEngine, "apparatusModel", &m_pApparatusCbbModel);
    MessageBox::SetEngine(m_pAppEngine);

//    QQmlContext *ctxt = p_qEngine.rootContext();
//    m_qProxyModel = new FilterData(this);

//    m_qProxyModel->setFilterRole(GymnastDataModel::SignalSection);
//    m_qProxyModel->setFilterRegExp("0");    // enum value of "SignalDoor"
//    connect(pGymModel, SIGNAL(OutputChanged(unsigned int)),
//            &m_cIoWrap, SLOT(SetOutput(unsigned int)));
}

void CoreApplication::Connect()
{
    QObject* saveScoreBtn = m_pAppEngine->rootObjects().first()->findChild<QObject*>("btnSaveScore");
    if (saveScoreBtn)
    {
        connect(saveScoreBtn, SIGNAL(saveScore(QString, QString, QString, QString)),
                SaveScore::Instance(), SLOT(onSaveScore(QString, QString, QString, QString)));
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
