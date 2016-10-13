#include "dbinterface.h"
#include <QDate>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

dbInterface* dbInterface::sm_pInstance = NULL;


dbInterface::dbInterface()
: dbIfaceBase()
{
}

dbInterface* dbInterface::Instance()
{
    if (sm_pInstance == NULL)
    {
        sm_pInstance = new dbInterface();
    }

    return sm_pInstance;
}

