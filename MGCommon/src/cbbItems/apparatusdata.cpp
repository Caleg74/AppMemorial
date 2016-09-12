#include "apparatusdata.h"

ApparatusData::ApparatusData(const int p_iApparatusId,
                             const QString& p_strNameIt,
                             const QString& p_strNameEn,
                             const QString& p_strGender)
: m_iApparatusId(p_iApparatusId)
, m_strGender(p_strGender)
{
    m_strName[ALangEn] = p_strNameEn;
    m_strName[ALangIt] = p_strNameIt;
}

int ApparatusData::getId() const
{
    return m_iApparatusId;
}

QString& ApparatusData::getName(ApparatusLanguage_t p_eLang)
{
    return m_strName[p_eLang];
}

QString& ApparatusData::getGender()
{
    return m_strGender;
}
