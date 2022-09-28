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
#include "athletedata.h"
#include <QDebug>
#include <math.h>
#include "arithmetictools.h"

AthleteData::AthleteData(const Gender_t p_eGender,
                         const int p_iAthleteId,
                         const QString& fullName,
                         const QString& nation,
                         const QString& imagePath)
    : m_eGender(p_eGender)
    , m_iAthleteId(p_iAthleteId)
    , m_iRank(0)
    , m_nameFull(fullName)
    , m_nationShort(nation)
    , m_imagePath(imagePath)
{
    int iApparatusMax;
    if (m_eGender == Male)
        iApparatusMax = ApparatusList::AMApparatusMax;
    else
        iApparatusMax = ApparatusList::AWApparatusMax;

    for (int i=0; i<iApparatusMax; i++)
    {
        SScore score = {0.0, 0.0, 0.0, false, false};
        m_vecScore.push_back(score);
    }
}

int AthleteData::getAthleteId()
{
    return m_iAthleteId;
}

void AthleteData::setRank(int p_iRank)
{
    m_iRank = p_iRank;
}

QString AthleteData::getRank() const
{
    return QString::number(m_iRank, 10);
}

QString AthleteData::getNameFull() const
{
    return m_nameFull;
}

QString AthleteData::getNationShort() const
{
    return m_nationShort;
}
QString AthleteData::getImagePath() const
{
    return m_imagePath;
}

void AthleteData::setIsFinalApparatusScore(int p_iApparatus, bool p_bIsFinalApparatus)
{
    if (m_eGender == Male)
    {
        if (p_iApparatus >= (ApparatusList::AMApparatusMax))
            qCritical() << "setStartScore(): p_iApparatus(M) " << p_iApparatus << " is out-of-range";
    }
    else
    {
        if (p_iApparatus >= (ApparatusList::AWApparatusMax))
            qCritical() << "setStartScore(): p_iApparatus(W) " << p_iApparatus << " is out-of-range";
    }

    m_vecScore[p_iApparatus].IsFinalApparatus = p_bIsFinalApparatus;
}

bool AthleteData::isFinalApparatusScore(int p_iApparatus) const
{
    if (m_eGender == Male)
    {
        if (p_iApparatus >= (ApparatusList::AMApparatusMax))
            qCritical() << "getFinalScore(): p_iApparatus(M) " << p_iApparatus << " is out-of-range";
    }
    else
    {
        if (p_iApparatus >= (ApparatusList::AWApparatusMax))
            qCritical() << "getFinalScore(): p_iApparatus(W) " << p_iApparatus << " is out-of-range";
    }

    return m_vecScore[p_iApparatus].IsFinalApparatus;
}

void AthleteData::setIsLatestScore(int p_iApparatus, bool p_bIsLatestScore)
{
    if (m_eGender == Male)
    {
        if (p_iApparatus >= (ApparatusList::AMApparatusMax))
            qCritical() << "setStartScore(): p_iApparatus(M) " << p_iApparatus << " is out-of-range";
    }
    else
    {
        if (p_iApparatus >= (ApparatusList::AWApparatusMax))
            qCritical() << "setStartScore(): p_iApparatus(W) " << p_iApparatus << " is out-of-range";
    }

    m_vecScore[p_iApparatus].IsLatestScore = p_bIsLatestScore;
}

bool AthleteData::isLatestScore(int p_iApparatus) const
{
    if (m_eGender == Male)
    {
        if (p_iApparatus >= (ApparatusList::AMApparatusMax))
            qCritical() << "getFinalScore(): p_iApparatus(M) " << p_iApparatus << " is out-of-range";
    }
    else
    {
        if (p_iApparatus >= (ApparatusList::AWApparatusMax))
            qCritical() << "getFinalScore(): p_iApparatus(W) " << p_iApparatus << " is out-of-range";
    }

    return m_vecScore[p_iApparatus].IsLatestScore;
}

void AthleteData::setStartScore(int p_iApparatus, float p_fScore)
{
    if (m_eGender == Male)
    {
        if (p_iApparatus >= (ApparatusList::AMApparatusMax))
            qCritical() << "setStartScore(): p_iApparatus(M) " << p_iApparatus << " is out-of-range";
    }
    else
    {
        if (p_iApparatus >= (ApparatusList::AWApparatusMax))
            qCritical() << "setStartScore(): p_iApparatus(W) " << p_iApparatus << " is out-of-range";
    }

    m_vecScore[p_iApparatus].StartScore = p_fScore;
}

QString AthleteData::getStartScore(int p_iApparatus) const
{
    if (m_eGender == Male)
    {
        if (p_iApparatus >= (ApparatusList::AMApparatusMax))
            qCritical() << "getStartScore(): p_iApparatus(M) " << p_iApparatus << " is out-of-range";
    }
    else
    {
        if (p_iApparatus >= (ApparatusList::AWApparatusMax))
            qCritical() << "getStartScore(): p_iApparatus(W) " << p_iApparatus << " is out-of-range";
    }

    if (fAreSame(m_vecScore[p_iApparatus].StartScore, 0.0f))
        return " - ";
    else
        return QString::number(m_vecScore[p_iApparatus].StartScore, 'f', 3);
}

void AthleteData::setExecutionScore(int p_iApparatus)
{
    if (m_eGender == Male)
    {
        if (p_iApparatus >= (ApparatusList::AMApparatusMax))
            qCritical() << "setFinalScore(): p_iApparatus(M) " << p_iApparatus << " is out-of-range";
    }
    else
    {
        if (p_iApparatus >= (ApparatusList::AWApparatusMax))
            qCritical() << "setFinalScore(): p_iApparatus(W) " << p_iApparatus << " is out-of-range";
    }

    m_vecScore[p_iApparatus].ExecutionScore = m_vecScore[p_iApparatus].FinalScore - m_vecScore[p_iApparatus].StartScore;
}

QString AthleteData::getExecutionScore(int p_iApparatus) const
{
    if (m_eGender == Male)
    {
        if (p_iApparatus >= (ApparatusList::AMApparatusMax))
            qCritical() << "getStartScore(): p_iApparatus(M) " << p_iApparatus << " is out-of-range";
    }
    else
    {
        if (p_iApparatus >= (ApparatusList::AWApparatusMax))
            qCritical() << "getStartScore(): p_iApparatus(W) " << p_iApparatus << " is out-of-range";
    }

    if (fAreSame(m_vecScore[p_iApparatus].ExecutionScore, 0.0f))
        return " - ";
    else
        return QString::number(m_vecScore[p_iApparatus].ExecutionScore, 'f', 3);
}

void AthleteData::setFinalScore(int p_iApparatus, float p_fScore)
{
    if (m_eGender == Male)
    {
        if (p_iApparatus >= (ApparatusList::AMApparatusMax))
            qCritical() << "setFinalScore(): p_iApparatus(M) " << p_iApparatus << " is out-of-range";
    }
    else
    {
        if (p_iApparatus >= (ApparatusList::AWApparatusMax))
            qCritical() << "setFinalScore(): p_iApparatus(W) " << p_iApparatus << " is out-of-range";
    }

    m_vecScore[p_iApparatus].FinalScore = p_fScore;
}

QString AthleteData::getFinalScore(int p_iApparatus) const
{
    if (m_eGender == Male)
    {
        if (p_iApparatus >= (ApparatusList::AMApparatusMax))
            qCritical() << "getFinalScore(): p_iApparatus(M) " << p_iApparatus << " is out-of-range";
    }
    else
    {
        if (p_iApparatus >= (ApparatusList::AWApparatusMax))
            qCritical() << "getFinalScore(): p_iApparatus(W) " << p_iApparatus << " is out-of-range";
    }

    if (fAreSame(m_vecScore[p_iApparatus].FinalScore, 0.0f))
        return " - ";
    else
        return QString::number(m_vecScore[p_iApparatus].FinalScore, 'f', 3);
}

void AthleteData::CalculateTotalScore()
{
    float fStartTot = 0;
    float fTot = 0;
    int iApparatusMax;
    if (m_eGender == Male)
        iApparatusMax   = ApparatusList::AMApparatusMax;
    else
        iApparatusMax   = ApparatusList::AWApparatusMax;

    for (int i=ApparatusList::AGFirstApparatus; i<iApparatusMax; i++)
    {
        fStartTot += m_vecScore[i].StartScore;
        fTot += m_vecScore[i].FinalScore;
    }

    m_vecScore[ApparatusList::AGTotalScore].StartScore = fStartTot;
    m_vecScore[ApparatusList::AGTotalScore].FinalScore = fTot;
}

bool AthleteData::operator<(const AthleteData other) const
{
    int iApparatusMax;
    if (m_eGender == Male)
        iApparatusMax   = ApparatusList::AMApparatusMax;
    else
        iApparatusMax   = ApparatusList::AWApparatusMax;

    // the filter model sorts the list with respect to the ranking, prior to that
    // the list must besorted out of the total score.
    // For this reason the total score must be calculated prior to this point

    // each return value is ! (inverted), since the sorting is not ascending but descending
    if (fAreSame(m_vecScore[ApparatusList::AGTotalScore].FinalScore,
                     other.m_vecScore[ApparatusList::AGTotalScore].FinalScore))
    {
        // 2nd criteria: remove the lowest score and check the total again
        QList<float> scoresThis;
        QList<float> scoresOther;

        // Fill the list with all final scores
        for (int i=ApparatusList::AGFirstApparatus; i<iApparatusMax; i++)
        {
            scoresThis << m_vecScore[i].FinalScore;
            scoresOther << other.m_vecScore[i].FinalScore;
        }
        // sort the list in ascending order, then remove the lowest score
        std::sort(scoresThis.begin(), scoresThis.end());
        std::sort(scoresOther.begin(), scoresOther.end());

        while (scoresThis.size() > 1)
        {
            scoresThis.removeFirst();
            scoresOther.removeFirst();

            float fSumThis = 0.0;
            float fSumOther = 0.0;
            // create the total with the remaining items
            for (int j=0; j<scoresThis.size(); j++)
            {
                fSumThis += scoresThis.at(j);
                fSumOther += scoresOther.at(j);
            }

            if (fALessThanB(fSumThis, fSumOther))
            {
                return !true;
            }
            else if (fAGreaterThanB(fSumThis, fSumOther))
            {
                return !false;
            }
            // if equal remove the next "lowest" score and try again
        }

        // 3rd criteria: the highest sum of all execution (E) scores
        // Fill the list with all execution scores
        float fSumExecThis = 0.0;
        float fSumExecOther = 0.0;

        for (int i=ApparatusList::AGFirstApparatus; i<iApparatusMax; i++)
        {
            fSumExecThis += m_vecScore[i].ExecutionScore;
            fSumExecOther += other.m_vecScore[i].ExecutionScore;
        }

        if (fALessThanB(fSumExecThis, fSumExecOther))
        {
            return !true;
        }
        else if (fAGreaterThanB(fSumExecThis, fSumExecOther))
        {
            return !false;
        }


        // 4th criteria: the highest sum of all start (D) scores
        // Fill the list with all execution scores
        float fSumStartThis = 0.0;
        float fSumStartOther = 0.0;

        for (int i=ApparatusList::AGFirstApparatus; i<iApparatusMax; i++)
        {
            fSumStartThis += m_vecScore[i].StartScore;
            fSumStartOther += other.m_vecScore[i].StartScore;
        }

        if (fALessThanB(fSumStartThis, fSumStartOther))
        {
            return !true;
        }
        else if (fAGreaterThanB(fSumStartOther, fSumStartOther))
        {
            return !false;
        }

        // at this pointit's probably everything = 0s...
        // sort alphabetically
        if (QString::compare(m_nameFull, other.m_nameFull) < 0)
            return true;
        else
            return false;
    }
    else if (fALessThanB(m_vecScore[ApparatusList::AGTotalScore].FinalScore,
                         other.m_vecScore[ApparatusList::AGTotalScore].FinalScore))
    {
     return !true;
    }
    else
    {
        return !false;
    }
}

bool operator== (const AthleteData& lhs, const AthleteData& rhs)
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

QDebug &operator<<(QDebug &stream, const AthleteData &obj)
{
    stream << "{" << obj.m_nameFull << ", ";
    stream << obj.m_iRank << ", ";
    stream << obj.m_vecScore[ApparatusList::AGTotalScore].FinalScore << "}\n";

    return stream;
}
