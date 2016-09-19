#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include "dbifacebase.h"
#include <QStringList>

class dbInterface : public dbIfaceBase
{
public:

    static dbInterface* Instance();

    int getNationId(QString& p_strNiceName);

    float getStartScore(const int p_iAthleteId, const int p_iApparatusId);

    float getFinalScore(const int p_iAthleteId, const int p_iApparatusId);

    int getForceScore(const int p_iAthleteId, const int p_iApparatusId);

private:

    /** Private constructor */
    dbInterface();

    static dbInterface* sm_pInstance;
};

#endif // DBINTERFACE_H
