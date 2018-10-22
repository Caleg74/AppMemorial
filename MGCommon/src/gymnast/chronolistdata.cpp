#include "chronolistdata.h"

ChronoListData::ChronoListData()
    : m_strGender("")
    , m_strApparatus("")
    , m_strNameFull("")
    , m_strImagePath("")
    , m_strNationShort("")
    , m_sScore()
    , m_fTotScore(0.0f)
    , m_iRank(0)
    , m_bLatestScore(false)
{
    m_sScore.StartScore = 0.0f;
    m_sScore.ExecutionScore = 0.0f;
    m_sScore.FinalScore = 0.0f;
    m_sScore.IsFinalApparatus = false;
}

ChronoListData::~ChronoListData()
{}

void ChronoListData::setGender(const QString& p_strGender)
{
    m_strGender = p_strGender;
}
QString ChronoListData::getGender() const
{
    return m_strGender;
}

void ChronoListData::setApparatusName(const QString& p_strApparatus)
{
    m_strApparatus = p_strApparatus;
}
QString ChronoListData::getApparatusName() const
{
    return m_strApparatus;
}

void ChronoListData::setNameFull(const QString& p_strFullName)
{
    m_strNameFull = p_strFullName;
}
QString ChronoListData::getNameFull() const
{
    return m_strNameFull;
}

void ChronoListData::setImagePath(const QString& p_strImagePath)
{
    m_strImagePath = p_strImagePath;
}

QString ChronoListData::getImagePath() const
{
    return m_strImagePath;
}

void ChronoListData::setNationShort(const QString& p_strNationShort)
{
    m_strNationShort = p_strNationShort;
}

QString ChronoListData::getNationShort() const
{
    return m_strNationShort;
}

void ChronoListData::setStartScore(const float p_fStartScore)
{
    m_sScore.StartScore = p_fStartScore;
}
QString ChronoListData::getStartScore() const
{
    return QString::number(m_sScore.StartScore, 'f', 3);
}

void ChronoListData::setExecutionScore(const float p_fExecutionScore)
{
    m_sScore.ExecutionScore = p_fExecutionScore;
}
QString ChronoListData::getExecutionScore() const
{
    return QString::number(m_sScore.ExecutionScore, 'f', 3);
}

void ChronoListData::setFinalScore(const float p_fFinalScore)
{
    m_sScore.FinalScore = p_fFinalScore;
}
QString ChronoListData::getFinalScore() const
{
    return QString::number(m_sScore.FinalScore, 'f', 3);
}

void ChronoListData::setTotScore(const float p_fTotScore)
{
    m_fTotScore = p_fTotScore;
}
QString ChronoListData::getTotScore() const
{
    return QString::number(m_fTotScore, 'f', 3);
}

void ChronoListData::setRank(const int p_iRank)
{
    m_iRank = p_iRank;
}
float ChronoListData::getRank() const
{
    return m_iRank;
}

void ChronoListData::setIsLatestScore(bool p_bIsLatestScore)
{
    m_bLatestScore = p_bIsLatestScore;
}

bool ChronoListData::isLatestScore() const
{
    return m_bLatestScore;
}

