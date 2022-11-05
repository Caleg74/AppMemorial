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
                              const float p_fDifficultyScore,
                              const float p_fExecutionScore,
                              const float p_fPenaltyScore,
                              const float p_fFinalScore,
                              const bool p_bFinalApparatus)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        query.prepare("INSERT INTO scores (sport_event_id, athlete_id, apparatus_id, difficulty_score, execution_score, penalty_score, final_score, final_apparatus) "
                           "VALUES (:sport_event_id, :athlete_id, :apparatus_id, :difficulty_score, :execution_score, :penalty_score, :final_score, :final_apparatus)");
        query.bindValue(":sport_event_id", p_iEventId);
        query.bindValue(":athlete_id", p_iAthleteId);
        query.bindValue(":apparatus_id", p_iApparatusId);
        query.bindValue(":difficulty_score", QString::number(p_fDifficultyScore, 'g', 6));
        query.bindValue(":execution_score", QString::number(p_fExecutionScore, 'g', 6));
        query.bindValue(":penalty_score", QString::number(p_fPenaltyScore, 'g', 6));
        query.bindValue(":final_score", QString::number(p_fFinalScore, 'g', 6));
        query.bindValue(":final_apparatus", QString::number((int)p_bFinalApparatus));

        bool bRet = query.exec();

        QString strFinalApparatus = p_bFinalApparatus ? "FinalApparatus" : "";
        if (bRet)
        {
            qInfo() << "Score added: " << p_iEventId << ", "
                                       << p_iAthleteId << ", "
                                       << p_iApparatusId << ", "
                                       << p_fDifficultyScore << ", "
                                       << p_fExecutionScore << ", "
                                       << p_fPenaltyScore << ", "
                                       << p_fFinalScore << ", "
                                       << strFinalApparatus;
        }
        else
        {
            qCritical() << "Score NOT added: " << p_iEventId << ", "
                                                << p_iAthleteId << ", "
                                                << p_iApparatusId << ", "
                                                << p_fDifficultyScore << ", "
                                                << p_fExecutionScore << ", "
                                                << p_fPenaltyScore << ", "
                                                << p_fFinalScore << ", "
                                                << strFinalApparatus;
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
                              const float p_fDifficultyScore,
                              const float p_fExecutionScore,
                              const float p_fPenaltyScore,
                              const float p_fFinalScore,
                              const bool p_bFinalApparatus)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        // UPDATE table_name
        //SET column1=value1,column2=value2,...
        //WHERE some_column=some_value;
        query.prepare("UPDATE scores SET difficulty_score = :difficulty_score, execution_score = :execution_score, penalty_score = :penalty_score, final_score = :final_score, final_apparatus = :final_apparatus "
                      "WHERE sport_event_id=:sport_event_id AND athlete_id=:athlete_id AND apparatus_id=:apparatus_id");
        query.bindValue(":difficulty_score", QString::number(p_fDifficultyScore, 'g', 6));
        query.bindValue(":execution_score", QString::number(p_fExecutionScore, 'g', 6));
        query.bindValue(":penalty_score", QString::number(p_fPenaltyScore, 'g', 6));
        query.bindValue(":final_score", QString::number(p_fFinalScore, 'g', 6));
        query.bindValue(":sport_event_id", p_iEventId);
        query.bindValue(":athlete_id", p_iAthleteId);
        query.bindValue(":apparatus_id", p_iApparatusId);
        query.bindValue(":final_apparatus", QString::number((int)p_bFinalApparatus));

        bool bRet = query.exec();

        QString strFinalApparatus = p_bFinalApparatus ? "FinalApparatus" : "";

        if (bRet)
        {
            qInfo() << "Score updated: " << p_iEventId << ", "
                                         << p_iAthleteId << ", "
                                         << p_iApparatusId << ", "
                                         << p_fDifficultyScore << ", "
                                         << p_fExecutionScore << ", "
                                         << p_fPenaltyScore << ", "
                                         << p_fFinalScore << ", "
                                         << strFinalApparatus;
        }
        else
        {
            qCritical() << "Score NOT updated: " << p_iEventId << ", "
                                                 << p_iAthleteId << ", "
                                                 << p_iApparatusId << ", "
                                                 << p_fDifficultyScore << ", "
                                                 << p_fExecutionScore << ", "
                                                 << p_fPenaltyScore << ", "
                                                 << p_fFinalScore << ", "
                                                 << strFinalApparatus;
            qCritical() << query.lastError();
        }
    }
    else
    {
        qInfo() << "dbInterface::updateScore(): Db not initialized";
    }
}

