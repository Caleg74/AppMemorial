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
#include "allroundmendata.h"

AllroundMenData::AllroundMenData(const QString &firstName,
                         const QString &lastName,
                         const QString &country,
                         const QString &sex)
    : m_firstName(firstName)
    , m_lastName(lastName)
    , m_country(country)
    , m_sex(sex)
{
}

QString AllroundMenData::FirstName() const
{
    return m_firstName;
}

QString AllroundMenData::LastName() const
{
    return m_lastName;
}

QString AllroundMenData::Country() const
{
    return m_country;
}

QString AllroundMenData::Sex() const
{
    return m_sex;
}

bool AllroundMenData::operator<(const AllroundMenData other) const
{
    int iCompare = QString::compare(m_firstName, other.m_firstName, Qt::CaseInsensitive);
    if (iCompare < 0)
    {
        return true;
    }
    else if (iCompare == 0)
    {
        iCompare = QString::compare(m_lastName, other.LastName(), Qt::CaseInsensitive);
        if (iCompare < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool operator== (const AllroundMenData& lhs, const AllroundMenData& rhs)
{
    if ( (lhs.FirstName() == rhs.FirstName())
      && (lhs.LastName() == rhs.LastName())
      && (lhs.Country() == rhs.Country())
      && (lhs.Sex() == rhs.Sex()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

QDebug &operator<<(QDebug &stream, const AllroundMenData &obj)
{
    stream << "{" << obj.m_firstName << ", ";
    stream << obj.m_lastName << ", ";
    stream << obj.m_sex << ", ";
    stream << obj.m_country << "}\n";

    return stream;
}
