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
    void getApparatusList(QStringList *p_pList, QString p_strGender);

    // for cbb
    void getRegisterdGymnastList(QStringList* p_pList);

    int getGymnastId(QString& p_firstName, QString& p_lastName);

    QString getGender(int p_iAthleteId);

    int getApparatusId(QString& p_apparatusName, QString &p_gender);

    void retrieveGymnastSubscriptionList(QList<QStringList> &p_strGymnList);

    int getNationId(QString& p_strNiceName);

    QString getNationName(int p_iNationId, enum NationInfo infoType);

    /** returns the eventId for the current event (based on year) */
    int getCurrentEventId();

    void setNewScore(const int p_iEventId,
                  const int p_iAthleteId,
                  const int p_iApparatusId,
                  const float p_fStartScore,
                  const float p_fFinalScore);

    void updateScore(const int p_iEventId,
                     const int p_iAthleteId,
                     const int p_iApparatusId,
                     const float p_fStartScore,
                     const float p_fFinalScore);

    bool isScorePresent(const int p_iEventId,
                        const int p_iAthleteId,
                        const int p_iApparatusId);
private:

    /** Private constructor */
    dbInterface();

    int m_iCurrentYear;

    static dbInterface* sm_pInstance;
};

#endif // DBINTERFACE_H
