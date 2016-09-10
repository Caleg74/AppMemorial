#ifndef ALLROUNMENDATA_H
#define ALLROUNMENDATA_H

#include <QString>
#include <QtCore>

class AllroundMenData
{
public:
    enum EApparatus
    {
        AFloor,
        APommelHores,
        ARings,
        AVault,
        AParallelBars,
        AHorizontalBar,
        AApparatusMax
    };

    typedef struct
    {
        float StartScore;
        float FinalScore;
    } SScore;

    AllroundMenData(const QString &fullName);

    void setRank(int p_iRank);
    QString getRank() const;
    QString getNameFull() const;
    void setTotalScore(float p_fTotScore);
    QString getTotalScore() const;
    void setStartScore(EApparatus p_eApparatus, float p_fScore);
    QString getStartScore(EApparatus p_eApparatus) const;
    void setFinalScore(EApparatus p_eApparatus, float p_fScore);
    QString getFinalScore(EApparatus p_eApparatus) const;

    void CalculateTotalScore();

    friend bool operator== (const AllroundMenData& lhs, const AllroundMenData& rhs);

    friend QDebug& operator<< (QDebug &stream, const AllroundMenData &obj);

    bool operator<(const AllroundMenData other) const;



private:
    int m_iRank;
    QString m_nameFull;
    float m_fTotalScore;
    SScore m_aiScore[AApparatusMax];
};



#endif // ALLROUNMENDATA_H
