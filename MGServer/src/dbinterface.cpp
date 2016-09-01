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

QString dbInterface::getNationNicename(int p_iNationId)
{
    QString strNicename;

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);

        query.exec("SELECT id,nicename FROM nations WHERE id = '" + QString::number(p_iNationId, 10) + "'");

        if (query.first())
        {
            strNicename = query.value(1).toString();
        }
        else
        {
            qCritical() << "No nicename found for Id: " << p_iNationId;
        }
    }
    else
    {
        qInfo() << "dbInterface::getNationNicename(): Db not initialized";
    }

    return strNicename;
}

void dbInterface::getGymnastList(QStringList* p_pList)
{

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        query.exec("SELECT first_name, last_name FROM athlete");

        *p_pList << "Ginnasta..";
        while (query.next())
        {
            QString name = query.value(0).toString();
            *p_pList << name;
        }
    }
    else
    {
        qInfo() << "dbInterface::getGymnassList(): Db not initialized";
    }
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

void dbInterface::RetrieveGymnastFromDb(QList<QStringList>& p_strGymnList)
{
    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        query.exec("SELECT first_name, last_name, gender, nation_id FROM athlete");

        while(query.next())
        {
            // Convert NationId to nicename
            QString strNationName = getNationNicename(query.value(3).toInt());

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
