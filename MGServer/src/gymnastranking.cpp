#include "gymnastranking.h"
#include "dbinterface.h"

GymnastRanking::GymnastRanking()
{
}

QList<AthleteData>* GymnastRanking::getAllroundMenList()
{
    return &m_MenList;
}

QList<AthleteData>* GymnastRanking::getAllroundWomenList()
{
    return &m_WomenList;
}

QList<SingleMWData>* GymnastRanking::getSingleMenList()
{
    return &m_singleMApparatusList;
}

QList<SingleMWData>* GymnastRanking::getSingleWomenList()
{
    return &m_singleWApparatusList;
}

void GymnastRanking::createLists()
{
    m_MenList.clear();
    m_WomenList.clear();
    m_singleMApparatusList.clear();
    m_singleWApparatusList.clear();

    retrieveGymnastList("M");
    retrieveGymnastList("F");
}

void GymnastRanking::retrieveGymnastList(const QString &p_strGender)
{
    QString firstName;
    QString lastName;
    QString countryFile;
    QString countryIso;
    QString countryIoc;
    int athleteId;

    Q_ASSERT((p_strGender == "F") || (p_strGender == "M"));

    AthleteData::Gender_t eGender = p_strGender == "F" ? AthleteData::Female : AthleteData::Male;
    QList<QStringList> p_strGymnList;
    dbInterface::Instance()->retrieveGymnastEventList(p_strGymnList);

    for (int i = 0; i < p_strGymnList.size();i++)
    {
        if (p_strGymnList.at(i)[3] == p_strGender)
        {
            firstName = p_strGymnList.at(i)[0];
            lastName = p_strGymnList.at(i)[1];
            countryIso = dbInterface::Instance()->getNationName(p_strGymnList.at(i)[2].toInt(), dbIfaceBase::NI_IsoName);
            countryFile = "qrc:/flags/" + countryIso.toLower() + ".svg";
            athleteId = dbInterface::Instance()->getGymnastId(firstName, lastName);
            countryIoc = dbInterface::Instance()->getNationName(p_strGymnList.at(i)[2].toInt(), dbIfaceBase::NI_IocName);

            AthleteData cAthlete(eGender, athleteId, firstName
                    + " " + lastName + "  ", countryIoc, countryFile);

            SingleMWData cSingleMW(athleteId, firstName
                    + " " + lastName + "  ", countryIoc, countryFile);

            if (p_strGender == "F")
            {
                m_WomenList << cAthlete;
                m_singleWApparatusList << cSingleMW;
            }
            else
            {
                m_MenList << cAthlete;
                m_singleMApparatusList << cSingleMW;
            }
        }
    }
}

void GymnastRanking::updateAllroundScores()
{
    updateAllroundMenScores();
    updateAllroundWomenScores();
}

void GymnastRanking::updateSingleScores(ApparatusList::EApparatusMen p_eAppMen)
{
    int iAppId;
    iAppId= ApparatusList::Instance()->getApparatusId((ApparatusList::EApparatusMen)p_eAppMen);

    updateSingleScores(iAppId, &m_singleMApparatusList);
}

void GymnastRanking::updateSingleScores(ApparatusList::EApparatusWomen p_eAppWomen)
{
    int iAppId;
    iAppId= ApparatusList::Instance()->getApparatusId((ApparatusList::EApparatusWomen)p_eAppWomen);

    updateSingleScores(iAppId, &m_singleWApparatusList);
}

void GymnastRanking::updateSingleScores(int p_iApparatusId, QList<SingleMWData>* p_pList)
{
    QList<SingleMWData>::iterator iter;

    for (iter = p_pList->begin(); iter != p_pList->end(); ++iter)
    {
        int iAthleteId = iter->getAthleteId();
        AllScores sAllScores = dbInterface::Instance()->getAllScores(iAthleteId, p_iApparatusId);
        float fTotalAllroundScore = dbInterface::Instance()->getAllroundTotalScore(iAthleteId);

        iter->setFinalScore(sAllScores.FinalScore);
        iter->setDifficultyScore(sAllScores.DifficultyScore);
        iter->setExecutionScore(sAllScores.ExecutionScore);
        iter->setPenaltyScore(sAllScores.PenaltyScore);
        iter->setForceScore(sAllScores.ForceScore);

        iter->setAllroundTotalScore(fTotalAllroundScore);
    }

    // sort the list
    std::sort(p_pList->begin(), p_pList->end());

    // the order defines the ranking as well
    int iRank = 1;
    for (iter = p_pList->begin(); iter != p_pList->end(); ++iter)
    {
        iter->setRank(iRank);
        iRank++;
    }
}

void GymnastRanking::updateAllroundMenScores()
{
    QList<AthleteData>::iterator iter;

    for (iter = m_MenList.begin(); iter != m_MenList.end(); ++iter)
    {
        for (int apparatus = ApparatusList::AGFirstApparatus; apparatus < ApparatusList::AMApparatusMax; apparatus++)
        {
            int iAthleteId = iter->getAthleteId();
            int iAppId = ApparatusList::Instance()->getApparatusId((ApparatusList::EApparatusMen)apparatus);
            float fDifficultyScore = dbInterface::Instance()->getDifficultyScore(iAthleteId, iAppId);
            float fFinalScore = dbInterface::Instance()->getFinalScore(iAthleteId, iAppId);

            iter->setFinalScore((ApparatusList::EApparatusMen)apparatus, fFinalScore);
            iter->setDifficultyScore((ApparatusList::EApparatusMen)apparatus, fDifficultyScore);
            iter->setExecutionScore((ApparatusList::EApparatusMen)apparatus);
        }
        iter->CalculateTotalScore();
    }

    // sort the list
    std::sort(m_MenList.begin(), m_MenList.end());

    // the order defines the ranking as well
    int iRank = 1;
    for (iter = m_MenList.begin(); iter != m_MenList.end(); ++iter)
    {
        iter->setRank(iRank);
        iRank++;
    }
}

void GymnastRanking::updateAllroundWomenScores()
{
    QList<AthleteData>::iterator iter;

    for (iter = m_WomenList.begin(); iter != m_WomenList.end(); ++iter)
    {
        for (int apparatus = ApparatusList::AGFirstApparatus; apparatus < ApparatusList::AWApparatusMax; apparatus++)
        {
            int iAthleteId = iter->getAthleteId();
            int iAppId = ApparatusList::Instance()->getApparatusId((ApparatusList::EApparatusWomen)apparatus);
            float fDifficultyScore = dbInterface::Instance()->getDifficultyScore(iAthleteId, iAppId);
            float fFinalScore = dbInterface::Instance()->getFinalScore(iAthleteId, iAppId);

            iter->setFinalScore((ApparatusList::EApparatusWomen)apparatus, fFinalScore);
            iter->setDifficultyScore((ApparatusList::EApparatusWomen)apparatus, fDifficultyScore);
            iter->setExecutionScore((ApparatusList::EApparatusWomen)apparatus);
        }
        iter->CalculateTotalScore();
    }

    // sort the list
    std::sort(m_WomenList.begin(), m_WomenList.end());

    // the order defines the ranking as well
    int iRank = 1;
    for (iter = m_WomenList.begin(); iter != m_WomenList.end(); ++iter)
    {
        iter->setRank(iRank);

        iRank++;
    }
}
