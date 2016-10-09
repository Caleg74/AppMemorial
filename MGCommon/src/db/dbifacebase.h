#ifndef DBIFACEBASE_H
#define DBIFACEBASE_H

#include "dbconnection.h"
#include <QStringList>

class dbIfaceBase : public dBConnection
{
public:

    enum NationInfo
    {
        NI_Nicename,
        NI_IocName,
        NI_IsoName
    };

    dbIfaceBase();

    // for cbb
    void getCountriesList(QStringList *p_pList);

    // for cbb
    void getRegisterdGymnastList(QStringList* p_pList);

    int getGymnastId(QString& p_firstName, QString& p_lastName);

    QString getGender(int p_iAthleteId);

    void retrieveRegisteredGymnastList(QList<QStringList> &p_strGymnList, NationInfo p_eNationType);

    int getNationId(QString& p_strNiceName);

    int getApparatusId(QString& p_apparatusName, QString &p_gender);

    QString getNationName(int p_iNationId, enum NationInfo infoType);

    /** returns the eventId for the current event (based on year) */
    int getCurrentEventId();

    bool isScorePresent(const int p_iEventId,
                        const int p_iAthleteId,
                        const int p_iApparatusId);

    void getApparatusList(QStringList* p_pList);

protected:

    int m_iCurrentYear;
};

#endif // DBIFACEBASE_H
