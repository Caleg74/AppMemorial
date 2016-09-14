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
#include "allroundwomendata.h"

AllroundWomenData::AllroundWomenData(const int p_iAthleteId,
                                 const QString& fullName,
                                 const QString& imagePath)
    : m_iAthleteId(p_iAthleteId)
    , m_iRank(0)
    , m_nameFull(fullName)
    , m_imagePath(imagePath)
    , m_fTotalScore(0)
{
    for (int i=0; i<ApparatusList::AWApparatusMax; i++)
    {
        m_aiScore[i].StartScore = 0;
        m_aiScore[i].FinalScore = 0;
    }
}

int AllroundWomenData::getAthleteId()
{
    return m_iAthleteId;
}

void AllroundWomenData::setRank(int p_iRank)
{
    m_iRank = p_iRank;
}

QString AllroundWomenData::getRank() const
{
    return QString::number(m_iRank, 10);
}

QString AllroundWomenData::getNameFull() const
{
    return m_nameFull;
}

QString AllroundWomenData::getImagePath() const
{
    return m_imagePath;
}

void AllroundWomenData::setTotalScore(float p_fTotScore)
{
    m_fTotalScore = p_fTotScore;
}

QString AllroundWomenData::getTotalScore() const
{
    return QString::number(m_fTotalScore, 'f', 3);
}

void AllroundWomenData::setStartScore(ApparatusList::EApparatusWomen p_eApparatus, float p_fScore)
{
    m_aiScore[p_eApparatus].StartScore = p_fScore;
}

QString AllroundWomenData::getStartScore(ApparatusList::EApparatusWomen p_eApparatus) const
{
    return QString::number(m_aiScore[p_eApparatus].StartScore, 'f', 3);
}

void AllroundWomenData::setFinalScore(ApparatusList::EApparatusWomen p_eApparatus, float p_fScore)
{
    m_aiScore[p_eApparatus].FinalScore = p_fScore;
}

QString AllroundWomenData::getFinalScore(ApparatusList::EApparatusWomen p_eApparatus) const
{
    return QString::number(m_aiScore[p_eApparatus].FinalScore, 'f', 3);
}

void AllroundWomenData::CalculateTotalScore()
{
    float fTot = 0;
    for (int i=0; i<ApparatusList::AWApparatusMax; i++)
    {
        fTot += m_aiScore[i].FinalScore;
    }

    m_fTotalScore = fTot;
}

bool AllroundWomenData::operator<(const AllroundWomenData other) const
{
    // the filter model sorts the list with respect to the ranking, prior to that
    // the list must besorted out of the total score.
    // For this reason the total score must be calculated prior to this point

    // each return value is ! (inverted), since the sorting is not ascending but descending
    if (m_fTotalScore < other.m_fTotalScore)
    {
        return !true;
    }
    else if (m_fTotalScore == other.m_fTotalScore)
    {
        // look for the highest note between the 2
        QList<int> scoresThis;
        QList<int> scoresOther;

        for (int i=0; i<ApparatusList::AWApparatusMax; i++)
        {
            scoresThis << m_aiScore[i].FinalScore;
            scoresOther << other.m_aiScore[i].FinalScore;
        }

        qSort(scoresThis);
        qSort(scoresOther);

        for (int i=ApparatusList::AWApparatusMax-1; i!= 0; i--)
        {
            if (scoresThis.at(i) > scoresOther.at(i))
                return !false;
            else if (scoresThis.at(i) < scoresOther.at(i))
                return !true;
            // else continue and compare the next score
        }

        return !true;
    }
    else
    {
        return !false;
    }
}

bool operator== (const AllroundWomenData& lhs, const AllroundWomenData& rhs)
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

QDebug &operator<<(QDebug &stream, const AllroundWomenData &obj)
{
    stream << "{" << obj.m_nameFull << ", ";
    stream << obj.m_iRank << ", ";
    stream << obj.m_fTotalScore << "}\n";

    return stream;
}
