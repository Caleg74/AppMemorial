#ifndef DBACCESS_H
#define DBACCESS_H

class dBConnection
{
public:

    dBConnection();

    ~dBConnection();

    bool initDb(bool p_bReadOnly);

    bool loadDriver();

protected:

    bool m_bInitialized;
};

#endif // DBACCESS_H
