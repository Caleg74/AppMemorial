#include "dbinterface.h"
#include <QDate>

dbInterface* dbInterface::sm_pInstance = NULL;


dbInterface::dbInterface()
: dBConnection()
{
    QDate qDate = QDate::currentDate();
    m_iCurrentYear = qDate.year();
}

dbInterface* dbInterface::Instance()
{
    if (sm_pInstance == NULL)
    {
        sm_pInstance = new dbInterface();
    }

    return sm_pInstance;
}

void dbInterface::getApparatusList(QStringList* p_pList)
{

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        query.exec("SELECT name_it FROM apparatus");

        *p_pList << "Attrezzo..";
        while (query.next())
        {
            QString name = query.value(0).toString();
            *p_pList << name;
        }
    }
    else
    {
        qInfo() << "dbInterface::getApparatusList(): Db not initialized";
    }
}

void dbInterface::getRegisterdGymnastList(QStringList* p_pList)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        query.exec("SELECT first_name, last_name, gender, nation_id FROM athlete");

        *p_pList << "Seleziona ginnasti..";

        while(query.next())
        {
            // Convert NationId to nicename
            QString strNationName = getNationName(query.value(3).toInt(), NI_ShortName);

            *p_pList << query.value(0).toString().trimmed() + ", "
                    + query.value(1).toString().trimmed() + ", ("
                    + strNationName.trimmed() + ")";
        }
    }
    else
    {
        qInfo() << "dbInterface::getRegisterdGymnastList(): Db not initialized";
    }
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

QString dbInterface::getNationName(int p_iNationId, enum NationInfo infoType)
{
    QString strName;

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);

        query.exec("SELECT id,nicename,iso3 FROM nations WHERE id = '" + QString::number(p_iNationId, 10) + "'");

        if (query.first())
        {
            int iValNbr = 1;
            switch(infoType)
            {
            case NI_Nicename:   iValNbr = 1; break;
            case NI_ShortName:  iValNbr = 2; break;
            default: qWarning() << "Invalid nation info " << infoType;
            }

            strName = query.value(iValNbr).toString();
        }
        else
        {
            qCritical() << "No name found for Id: " << p_iNationId;
        }
    }
    else
    {
        qInfo() << "dbInterface::getNationName(): Db not initialized";
    }

    return strName;
}


int dbInterface::getGymnastId(QString& p_firstName, QString& p_lastName)
{
    int athleteId = 0;

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);

        query.exec("SELECT id, first_name, last_name FROM athlete WHERE first_name = '" + p_firstName + "'"
                   " AND last_name = '" + p_lastName + "'");

        if (query.first())
        {
            athleteId = query.value(0).toInt();
        }
        else
        {
            qCritical() << "No Id found for : " << p_firstName << " "  << p_lastName;
        }
    }
    else
    {
        qInfo() << "dbInterface::getGymnastId(): Db not initialized";
    }

    return athleteId;
}
QString dbInterface::getGender(int p_iAthleteId)
{
    QString strGender;

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);

        query.exec("SELECT id, gender FROM athlete WHERE id = " + QString::number(p_iAthleteId, 10));

        if (query.first())
        {
            strGender = query.value(1).toString();
        }
        else
        {
            qCritical() << "No gender found for (athleteId)= " << p_iAthleteId;
        }
    }
    else
    {
        qInfo() << "dbInterface::getGender(): Db not initialized";
    }

    return strGender;
}

int dbInterface::getApparatusId(QString& p_apparatusName, QString& p_gender)
{
    int iApparatusId = 0;

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);

        QString strQuery = "SELECT id, name_it FROM apparatus WHERE name_it = '"
                + p_apparatusName + "' AND gender = '"
                + p_gender + "'";

        query.exec(strQuery);

        if (query.first())
        {
            iApparatusId = query.value(0).toInt();
        }
        else
        {
            qCritical() << "No Id found for: " << p_apparatusName << ", " << p_gender;
        }
    }
    else
    {
        qInfo() << "dbInterface::getApparatusId(): Db not initialized";
    }

    return iApparatusId;
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
                                 << getNationName(queryAthlete.value(3).toInt(), NI_ShortName);
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

int dbInterface::getCurrentEventId()
{
    int eventId = 0;

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);

        query.exec("SELECT id, year FROM sport_event");

        while (query.next())
        {
            if (query.value(1).toString().startsWith(QString::number(m_iCurrentYear, 10)))
            {
                eventId = query.value(0).toInt();
            }
        }

        if (eventId == 0)
        {
            qCritical() << "No Id found for event year: " << m_iCurrentYear;
        }
    }
    else
    {
        qInfo() << "dbInterface::getCurrentEventId(): Db not initialized";
    }

    return eventId;
}

void dbInterface::setScore(const int p_iEventId,
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
            qCritical() << "SAcore NOT added: " << p_iEventId << ", "
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
