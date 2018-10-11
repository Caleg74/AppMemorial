#ifndef CHRONOLISTDATA_H
#define CHRONOLISTDATA_H

#include "athletedata.h"
#include <QString>
#include <QVector>

class ChronoListData
{
public:
    ChronoListData();

    ~ChronoListData();

    void setGender(const QString& p_strGender);
    QString getGender() const;

    void setApparatusName(const QString& p_strApparatus);
    QString getApparatusName() const;

    void setNameFull(const QString& p_strFullName);
    QString getNameFull() const;

    void setImagePath(const QString& p_strImagePath);
    QString getImagePath() const;

    void setNationShort(const QString& p_strNationShort);
    QString getNationShort() const;

    void setStartScore(const float p_fStartScore);
    QString getStartScore() const;

    void setExecutionScore(const float p_fExecutionScore);
    QString getExecutionScore() const;

    void setFinalScore(const float p_fFinalScore);
    QString getFinalScore() const;

    void setTotScore(const float p_fFinalScore);
    QString getTotScore() const;

    void setRank(const int p_iRank);
    float getRank() const;

private:
    QString m_strGender;
    QString m_strApparatus;
    QString m_strNameFull;
    QString m_strImagePath;
    QString m_strNationShort;
    AthleteData::SScore m_sScore;
    float m_fTotScore;
    int m_iRank;
};

#endif // CHRONOLISTDATA_H
