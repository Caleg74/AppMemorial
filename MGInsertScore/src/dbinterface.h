#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include "dbconnection.h"
#include <QStringList>

class dbInterface : public dBConnection
{
public:
    enum NationInfo
    {
        NI_Nicename,
        NI_ShortName
    };

    static dbInterface* Instance();

    // for cbb
    void getApparatusList(QStringList *p_pList);

    // for cbb
    void getRegisterdGymnastList(QStringList* p_pList);

    int getGymnastId(QString& p_firstName, QString& p_lastName);

    void retrieveGymnastSubscriptionList(QList<QStringList> &p_strGymnList);

    int getNationId(QString& p_strNiceName);

    QString getNationName(int p_iNationId, enum NationInfo infoType);

    /** returns the eventId for the current event (based on year) */
    int getCurrentEventId();

private:

    /** Private constructor */
    dbInterface();

    int m_iCurrentYear;

    static dbInterface* sm_pInstance;
};

#endif // DBINTERFACE_H
