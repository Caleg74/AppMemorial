#ifndef ATHLETEDATA_H
#define ATHLETEDATA_H

#include <QString>
#include <QVector>
#include "apparatuslist.h"


class AthleteData
{
public:

    enum Gender_t
    {
        Male,
        Female
    };

    typedef struct
    {
        float StartScore;
        float FinalScore;
    } SScore;

    AthleteData(const Gender_t p_eGender,
                const int p_iAthleteId,
                const QString& fullName,
                const QString& imagePath);

    int getAthleteId();
    void setRank(int p_iRank);
    QString getRank() const;
    QString getNameFull() const;
    QString getImagePath() const;

    void setStartScore(int p_iApparatus, float p_fScore);
    QString getStartScore(int p_iApparatus) const;

    void setFinalScore(int p_iApparatus, float p_fScore);
    QString getFinalScore(int p_iApparatus) const;

    void CalculateTotalScore();

    friend bool operator== (const AthleteData& lhs, const AthleteData& rhs);

    friend QDebug& operator<< (QDebug &stream, const AthleteData &obj);

    bool operator<(const AthleteData other) const;



private:
    Gender_t m_eGender;
    int m_iAthleteId;
    int m_iRank;
    QString m_nameFull;
    QString m_imagePath;
    QVector<SScore> m_vecScore;
};



#endif // ATHLETEDATA_H
