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
    void getCountriesList(QStringList *p_pList);

    // for cbb
    void getRegisterdGymnastList(QStringList* p_pList);

    void insertGymnast(QString& p_strFirstName,
                       QString& p_strLastName,
                       QString& p_strGender,
                       int p_iNationId);

    void deleteGymnast(QString& p_strFirstName, QString& p_strLastName);

    int getGymnastId(QString& p_firstName, QString& p_lastName);

    void retrieveRegisteredGymnastList(QList<QStringList> &p_strGymnList);

    void retrieveGymnastSubscriptionList(QList<QStringList> &p_strGymnList);

    void subscribeGymnasttoEvent(int athleteId, int eventId);

    void deleteGymnastSubsscription(int athleteId, int eventId);

    bool isGymnastAlreadyRegistered(int p_iAthleteId, int p_iEventId);

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
