#ifndef SINGLEMWDATA_H
#define SINGLEMWDATA_H

#include <QString>
#include "apparatuslist.h"

class SingleMWData
{
public:


    typedef struct
    {
        float StartScore;
        float FinalScore;
        int   ForceScore;   // to be used only in case of equal score
    } SScore;

    SingleMWData(const int p_iAthleteId,
                 const QString& fullName,
                 const QString& nation,
                 const QString& imagePath);

    int getAthleteId();
    void setRank(int p_iRank);
    QString getRank() const;
    QString getNameFull() const;
    QString getNation() const;
    QString getImagePath() const;

    void setStartScore(float p_fScore);
    QString getStartScore() const;

    void setFinalScore(float p_fScore);
    QString getFinalScore() const;

    void setForceScore(int p_iForceScore);

    /** Sets the allround total score.
     *  It shall be used only in case of equal score */
    void setAllroundTotalScore(float p_fAllroundTotScore);

//    QString getForceScore() const;

    friend bool operator== (const SingleMWData& lhs, const SingleMWData& rhs);

    friend QDebug& operator<< (QDebug &stream, const SingleMWData &obj);

    bool operator<(const SingleMWData other) const;


private:
    int m_iAthleteId;
    int m_iRank;
    float m_fAllroundScore;    // just in case of equalscore
    QString m_nameFull;
    QString m_nation;
    QString m_imagePath;
    SScore m_sScore;
};



#endif // SINGLEMWDATA_H
