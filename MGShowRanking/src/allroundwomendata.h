#ifndef ALLROUNMENDATA_H
#define ALLROUNMENDATA_H

#include <QtCore>
#include "apparatuslist.h"

class AllroundWomenData
{
public:


    typedef struct
    {
        float StartScore;
        float FinalScore;
    } SScore;

    AllroundWomenData(const int p_iAthleteId,
                    const QString& fullName,
                    const QString& imagePath);

    int getAthleteId();
    void setRank(int p_iRank);
    QString getRank() const;
    QString getNameFull() const;
    QString getImagePath() const;
    void setTotalScore(float p_fTotScore);
    QString getTotalScore() const;
    void setStartScore(ApparatusList::EApparatusWomen p_eApparatus, float p_fScore);
    QString getStartScore(ApparatusList::EApparatusWomen p_eApparatus) const;
    void setFinalScore(ApparatusList::EApparatusWomen p_eApparatus, float p_fScore);
    QString getFinalScore(ApparatusList::EApparatusWomen p_eApparatus) const;

    void CalculateTotalScore();

    friend bool operator== (const AllroundWomenData& lhs, const AllroundWomenData& rhs);

    friend QDebug& operator<< (QDebug &stream, const AllroundWomenData &obj);

    bool operator<(const AllroundWomenData other) const;



private:
    int m_iAthleteId;
    int m_iRank;
    QString m_nameFull;
    QString m_imagePath;
    float m_fTotalScore;
    SScore m_aiScore[ApparatusList::AWApparatusMax];
};



#endif // ALLROUNMENDATA_H
