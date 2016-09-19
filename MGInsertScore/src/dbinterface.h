#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include "dbifacebase.h"
#include <QStringList>

class dbInterface : public dbIfaceBase
{
public:
    static dbInterface* Instance();

    int getNationId(QString& p_strNiceName);

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

private:

    /** Private constructor */
    dbInterface();

    static dbInterface* sm_pInstance;
};

#endif // DBINTERFACE_H
