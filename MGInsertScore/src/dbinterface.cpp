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

void dbInterface::setNewScore(const int p_iEventId,
                           const int p_iAthleteId,
                           const int p_iApparatusId,
                           const float p_fStartScore,
                           const float p_fFinalScore)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        query.prepare("INSERT INTO scores (sport_event_id, athlete_id, apparatus_id, start_score, final_score) "
                           "VALUES (:sport_event_id, :athlete_id, :apparatus_id, :start_score, :final_score)");
        query.bindValue(":sport_event_id", p_iEventId);
        query.bindValue(":athlete_id", p_iAthleteId);
        query.bindValue(":apparatus_id", p_iApparatusId);
        query.bindValue(":start_score", QString::number(p_fStartScore, 'g', 6));
        query.bindValue(":final_score", QString::number(p_fFinalScore, 'g', 6));

        bool bRet = query.exec();

        if (bRet)
        {
            qInfo() << "Score added: " << p_iEventId << ", "
                                       << p_iAthleteId << ", "
                                       << p_iApparatusId << ", "
                                       << p_fStartScore << ", "
                                       << p_fFinalScore;
        }
        else
        {
            qCritical() << "Score NOT added: " << p_iEventId << ", "
                                                << p_iAthleteId << ", "
                                                << p_iApparatusId << ", "
                                                << p_fStartScore << ", "
                                                << p_fFinalScore;
            qCritical() << query.lastError();
        }
    }
    else
    {
        qInfo() << "dbInterface::setScore(): Db not initialized";
    }
}

void dbInterface::updateScore(const int p_iEventId,
                           const int p_iAthleteId,
                           const int p_iApparatusId,
                           const float p_fStartScore,
                           const float p_fFinalScore)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        // UPDATE table_name
        //SET column1=value1,column2=value2,...
        //WHERE some_column=some_value;
        query.prepare("UPDATE scores SET start_score = :start_score, final_score = :final_score "
                      "WHERE sport_event_id=:sport_event_id AND athlete_id=:athlete_id AND apparatus_id=:apparatus_id");
        query.bindValue(":start_score", QString::number(p_fStartScore, 'g', 6));
        query.bindValue(":final_score", QString::number(p_fFinalScore, 'g', 6));
        query.bindValue(":sport_event_id", p_iEventId);
        query.bindValue(":athlete_id", p_iAthleteId);
        query.bindValue(":apparatus_id", p_iApparatusId);

        bool bRet = query.exec();

        if (bRet)
        {
            qInfo() << "Score updated: " << p_iEventId << ", "
                                         << p_iAthleteId << ", "
                                         << p_iApparatusId << ", "
                                         << p_fStartScore << ", "
                                         << p_fFinalScore;
        }
        else
        {
            qCritical() << "Score NOT updated: " << p_iEventId << ", "
                                                 << p_iAthleteId << ", "
                                                 << p_iApparatusId << ", "
                                                 << p_fStartScore << ", "
                                                 << p_fFinalScore;
            qCritical() << query.lastError();
        }
    }
    else
    {
        qInfo() << "dbInterface::updateScore(): Db not initialized";
    }
}

