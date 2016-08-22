#include "dbinterface.h"


dbInterface* dbInterface::sm_pInstance = NULL;


dbInterface::dbInterface()
: dBConnection()
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

void dbInterface::getCountriesList(QStringList* p_pList)
{

    if (m_bInitialized)
    {
        QSqlDatabase db = QSqlDatabase::database("ConnMG");
        QSqlQuery query(db);
        query.exec("SELECT nicename FROM nations");

        *p_pList << "nazione..";
        while (query.next())
        {
            QString name = query.value(0).toString();
            *p_pList << name;
        }
    }
}
