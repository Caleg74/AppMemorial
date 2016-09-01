#ifndef DBACCESS_H
#define DBACCESS_H

#include <QtSql>
#include <QString>

class dBConnection
{
public:

    dBConnection();

    ~dBConnection();

    bool initDb();

    bool loadDriver();

protected:

    QSqlDatabase m_qDB;

    bool m_bInitialized;
};

#endif // DBACCESS_H
