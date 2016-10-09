#include "dbinterface.h"
#include <QDate>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

dbInterface* dbInterface::sm_pInstance = NULL;


dbInterface::dbInterface()
: dbIfaceBase()
{
}

dbInterface* dbInterface::Instance()
{
    if (sm_pInstance == NULL)
    {
        sm_pInstance = new dbInterface();
    }

    return sm_pInstance;
}

int dbInterface::getNationId(QString& p_strNiceName)
{
    int iId = 0;

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);

        query.exec("SELECT id,nicename FROM nations WHERE nicename = '" + p_strNiceName + "'");

        if (query.first())
        {
            iId = query.value(0).toInt();
        }
        else
        {
            qCritical() << "No id found for nation: " << p_strNiceName;
        }
    }
    else
    {
        qInfo() << "dbInterface::getNationId(): Db not initialized";
    }

    return iId;
}

float dbInterface::getStartScore(const int p_iAthleteId, const int p_iApparatusId)
{
    float fScore = 0.0;

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);

        int iEventId = dbInterface::Instance()->getCurrentEventId();

         QString strQuery = "SELECT start_score FROM scores WHERE "
                   " sport_event_id = "   + QString::number(iEventId, 10) +
                   " AND athlete_id = "   + QString::number(p_iAthleteId, 10)+
                   " AND apparatus_id = " + QString::number(p_iApparatusId, 10);

         query.exec(strQuery);

        while (query.next())
        {
//            qDebug() << query.value(0).typeName()
//                    << ", " << query.value(0).toString();
            fScore = query.value(0).toFloat();
        }

        if (iEventId == 0)
        {
            qCritical() << "No Id found for event year: " << m_iCurrentYear;
        }
    }
    else
    {
        qInfo() << "dbInterface::getStartScore(): Db not initialized";
    }

    return fScore;
}

float dbInterface::getFinalScore(const int p_iAthleteId, const int p_iApparatusId)
{
    float fScore = 0.0;

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);

        int iEventId = dbInterface::Instance()->getCurrentEventId();

        QString strQuery = "SELECT final_score FROM scores WHERE "
                  " sport_event_id = "   + QString::number(iEventId, 10) +
                  " AND athlete_id = "   + QString::number(p_iAthleteId, 10)+
                  " AND apparatus_id = " + QString::number(p_iApparatusId, 10);

        query.exec(strQuery);

        while (query.next())
        {
            fScore = query.value(0).toFloat();
        }

        if (iEventId == 0)
        {
            qCritical() << "No Id found for event year: " << m_iCurrentYear;
        }
    }
    else
    {
        qInfo() << "dbInterface::getFinalScore(): Db not initialized";
    }

    return fScore;
}

int dbInterface::getForceScore(const int p_iAthleteId, const int p_iApparatusId)
{
    int iForceScore = 0;

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);

        int iEventId = dbInterface::Instance()->getCurrentEventId();

        QString strQuery = "SELECT force_score FROM scores WHERE "
                  " sport_event_id = "   + QString::number(iEventId, 10) +
                  " AND athlete_id = "   + QString::number(p_iAthleteId, 10)+
                  " AND apparatus_id = " + QString::number(p_iApparatusId, 10);

        query.exec(strQuery);

        while (query.next())
        {
            iForceScore = query.value(0).toInt();
        }

        if (iEventId == 0)
        {
            qCritical() << "No Id found for event year: " << m_iCurrentYear;
        }
    }
    else
    {
        qInfo() << "dbInterface::getForceScore(): Db not initialized";
    }

    return iForceScore;
}
