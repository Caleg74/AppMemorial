/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "singlemwdata.h"
#include <QDebug>
#include "arithmetictools.h"

SingleMWData::SingleMWData(const int p_iAthleteId,
                           const QString& fullName,
                           const QString &nation,
                           const QString& imagePath)
    : m_iAthleteId(p_iAthleteId)
    , m_iRank(0)
    , m_fAllroundScore(0.0)
    , m_nameFull(fullName)
    , m_nation(nation)
    , m_imagePath(imagePath)
{
    m_sScore.DifficultyScore = 0;
    m_sScore.FinalScore = 0;

}

int SingleMWData::getAthleteId()
{
    return m_iAthleteId;
}

void SingleMWData::setRank(int p_iRank)
{
    m_iRank = p_iRank;
}

QString SingleMWData::getRank() const
{
    return QString::number(m_iRank, 10);
}

QString SingleMWData::getNameFull() const
{
    return m_nameFull;
}

QString SingleMWData::getNation() const
{
    return m_nation;
}
QString SingleMWData::getImagePath() const
{
    return m_imagePath;
}

void SingleMWData::setDifficultyScore(float p_fScore)
{
    m_sScore.DifficultyScore = p_fScore;
}

QString SingleMWData::getDifficultyScore() const
{
    return QString::number(m_sScore.DifficultyScore, 'f', 3);
}

void SingleMWData::setExecutionScore(float p_fScore)
{
    m_sScore.ExecutionScore = p_fScore;
}

QString SingleMWData::getExecutionScore() const
{
    return QString::number(m_sScore.ExecutionScore, 'f', 3);
}

void SingleMWData::setPenaltyScore(float p_fScore)
{
    m_sScore.PenaltyScore = p_fScore;
}

QString SingleMWData::getPenaltyScore() const
{
    return QString::number(abs(m_sScore.PenaltyScore), 'f', 3);
}

void SingleMWData::setFinalScore(float p_fScore)
{
    m_sScore.FinalScore = p_fScore;
}

QString SingleMWData::getFinalScore() const
{
    return QString::number(m_sScore.FinalScore, 'f', 3);
}

void SingleMWData::setForceScore(int p_iForceScore)
{
    m_sScore.ForceScore = p_iForceScore;
}

void SingleMWData::setAllroundTotalScore(float p_fAllroundTotScore)
{
    m_fAllroundScore = p_fAllroundTotScore;
}

bool SingleMWData::operator<(const SingleMWData other) const
{
    // each return value is ! (inverted), since the sorting is not ascending but descending
    if (fALessThanB(m_sScore.FinalScore, other.m_sScore.FinalScore))
    {
        return !true;
    }
    else if (fAGreaterThanB(m_sScore.FinalScore, other.m_sScore.FinalScore))
    {
        return !false;
    }

    // 2nd criteria is execution score
    float fExecScoreThis = m_sScore.FinalScore - m_sScore.DifficultyScore;
    float fExecScoreOther = other.m_sScore.FinalScore - other.m_sScore.DifficultyScore;

    if (fALessThanB(fExecScoreThis, fExecScoreOther))
    {
        return !true;
    }
    else if (fAGreaterThanB(fExecScoreThis, fExecScoreOther))
    {
        return !false;
    }

    // 3rd criteria is the final Allround ranking
    if (fALessThanB(m_fAllroundScore, other.m_fAllroundScore))
    {
        return !true;
    }
    else if (fAGreaterThanB(m_fAllroundScore, other.m_fAllroundScore))
    {
        return !false;
    }


    // 4th criteria is  "manual flag" a force_score that makes the difference
    if (fALessThanB(m_sScore.ForceScore, other.m_sScore.ForceScore))
    {
        return !true;
    }
    else if (fAGreaterThanB(m_sScore.ForceScore, other.m_sScore.ForceScore))
    {
        return !false;
    }

    // at this pointit's probably everything = 0s...
    // sort alphabetically
    if (QString::compare(m_nameFull, other.m_nameFull) < 0)
        return true;
    else
        return false;

    return !false;
}

bool operator== (const SingleMWData& lhs, const SingleMWData& rhs)
{
    if (lhs.getNameFull() == rhs.getNameFull())
    {
        return true;
    }
    else
    {
        return false;
    }
}

QDebug &operator<<(QDebug &stream, const SingleMWData &obj)
{
    stream << "{" << obj.m_nameFull << ", ";
    stream << obj.m_iRank << ", ";
    stream << obj.m_sScore.FinalScore << " (";
    stream << obj.m_sScore.DifficultyScore << ") }\n";

    return stream;
}
