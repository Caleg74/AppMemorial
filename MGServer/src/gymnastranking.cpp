#include "gymnastranking.h"
#include "dbinterface.h"

GymnastRanking::GymnastRanking()
{
}

QList<AthleteData>* GymnastRanking::getMenList()
{
    return &m_MenList;
}

QList<AthleteData>* GymnastRanking::getWomenList()
{
    return &m_WomenList;
}

void GymnastRanking::createLists()
{
    m_MenList.clear();
    m_WomenList.clear();

    retrieveGymnastList("M");
    retrieveGymnastList("F");
}

void GymnastRanking::retrieveGymnastList(const QString &p_strGender)
{
    QString firstName;
    QString lastName;
    QString countryFile;
    int athleteId;

    Q_ASSERT((p_strGender == "F") || (p_strGender == "M"));

    AthleteData::Gender_t eGender = p_strGender == "F" ? AthleteData::Female : AthleteData::Male;
    QList<QStringList> p_strGymnList;
    dbInterface::Instance()->retrieveRegisteredGymnastList(p_strGymnList, dbIfaceBase::NI_IsoName);

    for (int i = 0; i < p_strGymnList.size();i++)
    {
        if (p_strGymnList.at(i)[3] == p_strGender)
        {
            firstName = p_strGymnList.at(i)[0];
            lastName = p_strGymnList.at(i)[1];
            countryFile = "qrc:/flags/" + (p_strGymnList.at(i)[2]).toLower() + ".svg";
            athleteId = dbInterface::Instance()->getGymnastId(firstName, lastName);

            AthleteData cAthlete(eGender, athleteId, firstName
                    + " " + lastName + "  ", countryFile);

            if (p_strGender == "F")
                m_WomenList << cAthlete;
            else
                m_MenList << cAthlete;
        }
    }
}

void GymnastRanking::updateScores()
{
    updateMenScores();
    updateWomenScores();
}

void GymnastRanking::updateMenScores()
{
    QList<AthleteData>::iterator iter;

    for (iter = m_MenList.begin(); iter != m_MenList.end(); ++iter)
    {
        for (int apparatus = ApparatusList::AGFirstApparatus; apparatus < ApparatusList::AMApparatusMax; apparatus++)
        {
            int iAthleteId = iter->getAthleteId();
            int iAppId = ApparatusList::Instance()->getApparatusId((ApparatusList::EApparatusMen)apparatus);
            float fStartScore = dbInterface::Instance()->getStartScore(iAthleteId, iAppId);
            float fFinalScore = dbInterface::Instance()->getFinalScore(iAthleteId, iAppId);

            iter->setFinalScore((ApparatusList::EApparatusMen)apparatus, fFinalScore);
            iter->setStartScore((ApparatusList::EApparatusMen)apparatus, fStartScore);
        }
        iter->CalculateTotalScore();
    }

    // sort the list
    qSort(m_MenList);

    // the order defines the ranking as well
    int iRank = 1;
    for (iter = m_MenList.begin(); iter != m_MenList.end(); ++iter)
    {
        iter->setRank(iRank);
        iRank++;
    }
}

void GymnastRanking::updateWomenScores()
{
    QList<AthleteData>::iterator iter;

    for (iter = m_WomenList.begin(); iter != m_WomenList.end(); ++iter)
    {
        for (int apparatus = ApparatusList::AGFirstApparatus; apparatus < ApparatusList::AWApparatusMax; apparatus++)
        {
            int iAthleteId = iter->getAthleteId();
            int iAppId = ApparatusList::Instance()->getApparatusId((ApparatusList::EApparatusWomen)apparatus);
            float fStartScore = dbInterface::Instance()->getStartScore(iAthleteId, iAppId);
            float fFinalScore = dbInterface::Instance()->getFinalScore(iAthleteId, iAppId);

            iter->setFinalScore((ApparatusList::EApparatusWomen)apparatus, fFinalScore);
            iter->setStartScore((ApparatusList::EApparatusWomen)apparatus, fStartScore);
        }
        iter->CalculateTotalScore();
    }

    // sort the list
    qSort(m_WomenList);

    // the order defines the ranking as well
    int iRank = 1;
    for (iter = m_WomenList.begin(); iter != m_WomenList.end(); ++iter)
    {
        iter->setRank(iRank);
        iRank++;
    }
}
