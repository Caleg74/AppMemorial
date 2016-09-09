#ifndef ALLROUNMENDATA_H
#define ALLROUNMENDATA_H

#include <QString>
#include <QtCore>

class AllroundMenData
{
public:
    AllroundMenData(const QString &firstName,
                const QString &lastName,
                const QString &country,
                const QString &sex);

    QString FirstName() const;
    QString LastName() const;
    QString Country() const;
    QString Sex() const;

    friend bool operator== (const AllroundMenData& lhs, const AllroundMenData& rhs);

    friend QDebug& operator<< (QDebug &stream, const AllroundMenData &obj);

    bool operator<(const AllroundMenData other) const;



private:
    QString m_firstName;
    QString m_lastName;
    QString m_country;
    QString m_sex;
};



#endif // ALLROUNMENDATA_H
