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

void dbInterface::getCountriesList(QStringList* p_pList)
{

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        query.exec("SELECT nicename FROM nations");

        *p_pList << "Nazione..";
        while (query.next())
        {
            QString name = query.value(0).toString();
            *p_pList << name;
        }
    }
    else
    {
        qInfo() << "dbInterface::getCountriesList(): Db not initialized";
    }
}

void dbInterface::getRegisterdGymnastList(QStringList* p_pList)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        query.exec("SELECT first_name, last_name, gender, nation_id FROM athlete");

        while(query.next())
        {
            // Convert NationId to nicename
            QString strNationName = getNationName(query.value(3).toInt(), NI_ShortName);

            *p_pList << query.value(0).toString().trimmed() + ", "
                    + query.value(1).toString().trimmed() + ", ("
                    + strNationName.trimmed() + ")";
        }

        qSort(*p_pList);

        // put it at the beginning
        p_pList->insert(p_pList->begin(), "Seleziona ginnasti..");
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
            qCritical() << "Athlete NOT removed: " << p_strFirstName << " " << p_strLastName;
            qCritical() << query.lastError();
        }
    }
    else
    {
        qInfo() << "dbInterface::deleteGymnast(): Db not initialized";
    }
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

void dbInterface::retrieveRegisteredGymnastList(QList<QStringList>& p_strGymnList)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        query.exec("SELECT first_name, last_name, gender, nation_id FROM athlete");

        while(query.next())
        {
            // Convert NationId to nicename
            QString strNationName = getNationName(query.value(3).toInt(), NI_Nicename);

            QStringList strData;
            strData << query.value(0).toString().trimmed()
                    << query.value(1).toString().trimmed()
                    << strNationName.trimmed()
                    << query.value(2).toString().trimmed();

            p_strGymnList << strData;
            qInfo() << "Athlete retrieved: " << strData;
        }
    }
    else
    {
        qInfo() << "dbInterface::insertGymnast(): Db not initialized";
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
