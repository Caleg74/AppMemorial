#include "dbconnection.h"

dBConnection::dBConnection()
 : m_qDB()
 , m_bInitialized(false)
{
}

dBConnection::~dBConnection()
{
    QSqlDatabase::removeDatabase(QString("ConnMG"));
}

bool dBConnection::loadDriver()
{
    bool bRet = false;

    // OCDB with conection name
    if (QSqlDatabase::drivers().contains("QOCDB"))
    {
        bRet = true;
    }
    else
    {
        qCritical() << "Database driver not loaded";
    }

    return bRet;
}

bool dBConnection::initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "ConnMG");
    db.setDatabaseName("PostgreSQL35W");
    db.setHostName("localhost");
    db.setPort(5432);

    if (db.open())
    {
        m_bInitialized = true;
    }
    else
    {
        m_bInitialized = false;
        qCritical() << "DbError: " << db.lastError();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(QString("ConnMG"));
    }

    //    connectionWidget->refresh();

    return m_bInitialized;
}
