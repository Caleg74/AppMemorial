#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include "dbconnection.h"
#include <QStringList>

class dbInterface : public dBConnection
{
public:

    static dbInterface* Instance();

    void getCountriesList(QStringList *p_pList);

private:

    dbInterface();

    static dbInterface* sm_pInstance;
};

#endif // DBINTERFACE_H
