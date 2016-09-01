#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include "dbconnection.h"
#include <QStringList>

class dbInterface : public dBConnection
{
public:

    static dbInterface* Instance();

    void getCountriesList(QStringList *p_pList);

    /** Returns the gymnasts for this year.
     *  The year is determined by reading the PC date
     */
    void getGymnastList(QStringList* p_pList);

    void insertGymnast(QString& p_strFirstName,
                       QString& p_strLastName,
                       QString& p_strGender,
                       int p_iNationId);

    void deleteGymnast(QString& p_strFirstName, QString& p_strLastName);

    void RetrieveGymnastFromDb(QList<QStringList> &p_strGymnList);

    int getNationId(QString& p_strNiceName);

    QString getNationNicename(int p_iNationId);

private:

    /** Private constructor */
    dbInterface();

    int m_iCurrentYear;

    static dbInterface* sm_pInstance;
};

#endif // DBINTERFACE_H
