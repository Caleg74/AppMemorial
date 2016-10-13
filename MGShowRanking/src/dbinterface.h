#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include "dbifacebase.h"
#include <QStringList>

class dbInterface : public dbIfaceBase
{
public:

    static dbInterface* Instance();

private:

    /** Private constructor */
    dbInterface();

    static dbInterface* sm_pInstance;
};

#endif // DBINTERFACE_H
