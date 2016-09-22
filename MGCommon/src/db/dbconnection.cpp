#include "dbconnection.h"
#include <QtSql>

dBConnection::dBConnection()
 : m_bInitialized(false)
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
    if (QSqlDatabase::drivers().contains("QODBC"))
    {
        bRet = true;
    }
    else
    {
        qCritical() << "Database driver QODBC not loaded";
    }

    return bRet;
}

bool dBConnection::initDb(bool p_bReadOnly)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "ConnMG");
    if (p_bReadOnly)
        db.setDatabaseName("PostgreSQL35R");    // Readonly access user!
    else
        db.setDatabaseName("PostgreSQL35W");    // R/W access user!

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
