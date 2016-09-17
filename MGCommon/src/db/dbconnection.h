#ifndef DBACCESS_H
#define DBACCESS_H

class dBConnection
{
public:

    dBConnection();

    ~dBConnection();

    bool initDb();

    bool loadDriver();

protected:

    bool m_bInitialized;
};

#endif // DBACCESS_H
