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
        m_strlastError = "No error";
        bRet = true;
    }
    else
    {
        m_strlastError = "Database driver QODBC not loaded";
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
        m_strlastError = "No error";
        m_bInitialized = true;
    }
    else
    {
        m_bInitialized = false;
        m_strlastError = db.lastError().text();
        qCritical() << "DbError: " << db.lastError();
        QSqlDatabase::removeDatabase(QString("ConnMG"));
    }

    //    connectionWidget->refresh();

    return m_bInitialized;
}

QString& dBConnection::getLastError()
{
    return m_strlastError;
}
