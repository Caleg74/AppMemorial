#ifndef ALLROUNWOMENDATA_H
#define ALLROUNWOMENDATA_H

#include <QString>
#include "apparatuslist.h"

class AllroundMenData
{
public:


    typedef struct
    {
        float StartScore;
        float FinalScore;
    } SScore;

    AllroundMenData(const int p_iAthleteId,
                    const QString& fullName,
                    const QString& imagePath);

    int getAthleteId();
    void setRank(int p_iRank);
    QString getRank() const;
    QString getNameFull() const;
    QString getImagePath() const;

    void setStartScore(ApparatusList::EApparatusMen p_eApparatus, float p_fScore);
    QString getStartScore(ApparatusList::EApparatusMen p_eApparatus) const;

    void setFinalScore(ApparatusList::EApparatusMen p_eApparatus, float p_fScore);
    QString getFinalScore(ApparatusList::EApparatusMen p_eApparatus) const;

    void CalculateTotalScore();

    friend bool operator== (const AllroundMenData& lhs, const AllroundMenData& rhs);

    friend QDebug& operator<< (QDebug &stream, const AllroundMenData &obj);

    bool operator<(const AllroundMenData other) const;



private:
    int m_iAthleteId;
    int m_iRank;
    QString m_nameFull;
    QString m_imagePath;
    SScore m_aiScore[ApparatusList::AMApparatusMax];
};



#endif // ALLROUNWOMENDATA_H
