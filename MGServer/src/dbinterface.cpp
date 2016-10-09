#include "dbinterface.h"
#include <QDate>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "messagebox.h"

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

void dbInterface::insertGymnast(QString& p_strFirstName,
                   QString& p_strLastName,
                   QString& p_strGender,
                   int p_iNationId)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        query.prepare("INSERT INTO athlete (first_name, last_name, gender, nation_id) "
                           "VALUES (:first_name, :last_name, :gender, :nation_id)");
        query.bindValue(":first_name", p_strFirstName);
        query.bindValue(":last_name", p_strLastName);
        query.bindValue(":gender", p_strGender);
        query.bindValue(":nation_id", p_iNationId);

        bool bRet = query.exec();

        if (bRet)
        {
            qInfo() << "Athlete added: " << p_strFirstName << " " << p_strLastName;
        }
        else
        {
            qCritical() << "Athlete NOT added: " << p_strFirstName << " " << p_strLastName;
            qCritical() << query.lastError();
        }
    }
    else
    {
        qInfo() << "dbInterface::insertGymnast(): Db not initialized";
    }
}

void dbInterface::deleteGymnast(QString& p_strFirstName, QString& p_strLastName)
{

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        QString strQuery = "DELETE FROM athlete WHERE first_name='" + p_strFirstName
                + "' AND last_name='" + p_strLastName.trimmed() + "'";
        bool bRet = query.exec(strQuery);

        if (bRet)
        {
            qInfo() << "Athlete removed: " << p_strFirstName << " " << p_strLastName;
        }
        else
        {
            QString strErr = "Athlete NOT removed: " + p_strFirstName + " " + p_strLastName
                    +  "\n" + query.lastError().text();
            qCritical() << strErr;

            MessageBox cMsgBox;
            cMsgBox.SetTitle("Warning");
            cMsgBox.SetText(strErr);
            cMsgBox.Show();
        }
    }
    else
    {
        qInfo() << "dbInterface::deleteGymnast(): Db not initialized";
    }
}

void dbInterface::retrieveGymnastSubscriptionList(QList<QStringList>& p_strGymnList)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery queryAthlete(db);
        QSqlQuery querySportEventSub(db);


        querySportEventSub.exec("SELECT athlete_id, sport_event_id FROM sport_event_subscriptions");

        while (querySportEventSub.next())
        {
            QString athleteId = querySportEventSub.value(0).toString();
            QString eventId = querySportEventSub.value(1).toString();

            queryAthlete.exec("SELECT id, first_name, last_name, nation_id FROM athlete WHERE id=" + athleteId);

            QStringList gymnastSubscript;
            if (queryAthlete.first())
            {

                // add full name
                gymnastSubscript << athleteId
                                 << eventId
                                 << queryAthlete.value(1).toString().trimmed()
                                 << queryAthlete.value(2).toString().trimmed()
                                 << getNationName(queryAthlete.value(3).toInt(), NI_IocName);
            }
            else
            {
                qCritical() << "No athlete found for Id: " << athleteId;
            }

            p_strGymnList  << gymnastSubscript;
        }
    }
    else
    {
        qInfo() << "dbInterface::getGymnastSelectList(): Db not initialized";
    }
}

void dbInterface::subscribeGymnasttoEvent(int athleteId, int eventId)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        query.prepare("INSERT INTO sport_event_subscriptions (athlete_id, sport_event_id) "
                           "VALUES (:athlete_id, :sport_event_id)");
        query.bindValue(":athlete_id", athleteId);
        query.bindValue(":sport_event_id", eventId);

        bool bRet = query.exec();

        if (bRet)
        {
            qInfo() << "Athlete subscribed: " << athleteId << " to event: " << eventId;
        }
        else
        {
            qCritical() << "Athlete NOT sunscribed: " << athleteId << " to event: " << eventId;
            qCritical() << query.lastError();
        }
    }
    else
    {
        qInfo() << "dbInterface::subscribeGymnasttoEvent(): Db not initialized";
    }
}

void dbInterface::deleteGymnastSubsscription(int athleteId, int eventId)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        QString strQuery = "DELETE FROM sport_event_subscriptions WHERE "
                           "athlete_id ='" + QString::number(athleteId, 10) + "' AND "
                           "sport_event_id='" + QString::number(eventId, 10) + "'";

        bool bRet = query.exec(strQuery);

        if (bRet)
        {
            qInfo() << "Athlete unsubribed: " << athleteId << " to event: " << eventId;
        }
        else
        {
            qCritical() << "Athlete NOT unsubscribed: " << athleteId << " to event: " << eventId;
            qCritical() << query.lastError();
        }
    }
    else
    {
        qInfo() << "dbInterface::deleteGymnastSubsscription(): Db not initialized";
    }
}

bool dbInterface::isGymnastAlreadyRegistered(int p_iAthleteId, int p_iEventId)
{
    bool bAthleteFound = false;

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery querySportEventSub(db);


        querySportEventSub.exec("SELECT athlete_id, sport_event_id FROM sport_event_subscriptions WHERE "
                                "athlete_id ='" + QString::number(p_iAthleteId, 10) + "' AND "
                                "sport_event_id='" + QString::number(p_iEventId, 10) + "'");

        if (querySportEventSub.first())
        {
            bAthleteFound = true;
        }
    }

    return bAthleteFound;
}

void dbInterface::updateForceScore(const int p_iEventId,
                           const int p_iAthleteId,
                           const int p_iApparatusId,
                           const int p_iForceScore)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        // UPDATE table_name
        //SET column1=value1,column2=value2,...
        //WHERE some_column=some_value;
        query.prepare("UPDATE scores SET force_score = :force_score "
                      "WHERE sport_event_id=:sport_event_id AND athlete_id=:athlete_id AND apparatus_id=:apparatus_id");
        query.bindValue(":force_score", QString::number(p_iForceScore, 'g', 6));
        query.bindValue(":sport_event_id", p_iEventId);
        query.bindValue(":athlete_id", p_iAthleteId);
        query.bindValue(":apparatus_id", p_iApparatusId);

        bool bRet = query.exec();

        if (bRet)
        {
            qInfo() << "Score updated: " << p_iEventId << ", "
                                         << p_iAthleteId << ", "
                                         << p_iApparatusId << ", "
                                         << p_iForceScore;
        }
        else
        {
            qCritical() << "Score NOT updated: " << p_iEventId << ", "
                                                 << p_iAthleteId << ", "
                                                 << p_iApparatusId << ", "
                                                 << p_iForceScore;
            qCritical() << query.lastError();
        }
    }
    else
    {
        qInfo() << "dbInterface::updateScore(): Db not initialized";
    }
}

void dbInterface::eraseAllForcedScore(const int p_iEventId)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);

        query.prepare("UPDATE scores SET force_score = 0 "
                      "WHERE sport_event_id=:sport_event_id");
        query.bindValue(":sport_event_id", p_iEventId);

        bool bRet = query.exec();

        if (bRet)
        {
            qInfo() << "All Forced Score reset for Event: " << p_iEventId;
        }
        else
        {
            qCritical() << "Score Forced Score reset FAILED";
            qCritical() << query.lastError();
        }
    }
    else
    {
        qInfo() << "dbInterface::updateScore(): Db not initialized";
    }
}
