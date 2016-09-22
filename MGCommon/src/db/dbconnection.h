#ifndef DBACCESS_H
#define DBACCESS_H

#include <QString>
class dBConnection
{
public:

    dBConnection();

    ~dBConnection();

    bool initDb(bool p_bReadOnly);

    bool loadDriver();

    QString& getLastError();

protected:

    bool m_bInitialized;

    QString m_strlastError;
};

#endif // DBACCESS_H
