#include "allroundwomendatamodel.h"
#include "dbinterface.h"
#include "sortfilterproxymodel.h"

//**** STATIC MEMBER INITIALIZATION *********************

AllroundWomenDataModel::AllroundWomenDataModel(QObject *parent)
    : GymnastDataModel(parent)
{
    RetrieveGymnastList();

}

AllroundWomenDataModel::~AllroundWomenDataModel()
{
    m_rankingList.clear();
}

void AllroundWomenDataModel::RetrieveGymnastList()
{
    QString firstName;
    QString lastName;
    QString countryIso;
    QString countryIoc;
    QString countryFile;
    int athleteId;

    QList<QStringList> p_strGymnList;
    dbInterface::Instance()->retrieveRegisteredGymnastList(p_strGymnList);

    for (int i = 0; i < p_strGymnList.size();i++)
    {
        if (p_strGymnList.at(i)[3] == "F")  // only Women ranking here
        {
            firstName = p_strGymnList.at(i)[0];
            lastName = p_strGymnList.at(i)[1];
            countryIso = dbInterface::Instance()->getNationName(p_strGymnList.at(i)[2].toInt(), dbIfaceBase::NI_IsoName);
            countryIoc = dbInterface::Instance()->getNationName(p_strGymnList.at(i)[2].toInt(), dbIfaceBase::NI_IocName);
            countryFile = "qrc:/flags/" + countryIso.toLower() + ".svg";
            athleteId = dbInterface::Instance()->getGymnastId(firstName, lastName);
            AthleteData cAllroundWomen(AthleteData::Female, athleteId, firstName
                    + " " + lastName + "  ", countryIoc, countryFile);

            beginInsertRows(QModelIndex(), rowCount(), rowCount());
            m_rankingList << cAllroundWomen;
            endInsertRows();
        }
    }
}

void AllroundWomenDataModel::updateScores()
{
    QList<AthleteData>::iterator iter;

    for (iter = m_rankingList.begin(); iter != m_rankingList.end(); ++iter)
    {
        for (int apparatus = ApparatusList::AGFirstApparatus; apparatus < ApparatusList::AWApparatusMax; apparatus++)
        {
            int iAthleteId = iter->getAthleteId();
            int iAppId = ApparatusList::Instance()->getApparatusId((ApparatusList::EApparatusWomen)apparatus);
            float fStartScore = dbInterface::Instance()->getStartScore(iAthleteId, iAppId);
            float fFinalScore = dbInterface::Instance()->getFinalScore(iAthleteId, iAppId);

//            float fFinalRandom = (float)(qrand() % ((15000 + 1) - 10000) + 10000) / 1000;
//            float fStartRandom = fFinalRandom - 10;
            iter->setFinalScore((ApparatusList::EApparatusWomen)apparatus, fFinalScore);
            iter->setStartScore((ApparatusList::EApparatusWomen)apparatus, fStartScore);
        }
        iter->CalculateTotalScore();
    }

    // sort the list
    qSort(m_rankingList);

    // the order defines the ranking as well
    int iRank = 1;
    for (iter = m_rankingList.begin(); iter != m_rankingList.end(); ++iter)
    {
        iter->setRank(iRank);
        iRank++;
    }

    // update all model
    emit dataChanged(index(0, 0), index(rowCount() - 1, 0));

}


//void AllroundWomenDataModel::addItem(QString nameFull)
//{

//    int iNationId = dbInterface::Instance()->getNationId(country);

//    AllroundWomenData cAllroundWomen(nameFull);

//    // add it to the database
//    dbInterface::Instance()->insertGymnast(firstName, lastName, sex, iNationId);

//    beginInsertRows(QModelIndex(), rowCount(), rowCount());
//cAllroundWomen    endInsertRows();
//}

//void AllroundWomenDataModel::removeItem(QString nameFull)
//{
//    AllroundWomenData* pItem = GetItem(firstName, lastName);

//    QModelIndex pIndex = indexFromItem(pItem);

//    // add it to the database
//    dbInterface::Instance()->deleteGymnast(firstName, lastName);

//    beginRemoveRows(QModelIndex(), pIndex.row(), pIndex.row());
//    m_rankingList.removeAt(pIndex.row());
//    endRemoveRows();
//}

int AllroundWomenDataModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_rankingList.count();
}

QVariant AllroundWomenDataModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_rankingList.count())
        return QVariant();

    const AthleteData &gymnast = m_rankingList[index.row()];
    if (role == RankRole)
        return gymnast.getRank();
    else if (role == NameFullRole)
        return gymnast.getNameFull();
    else if (role == FlagImageRole)
        return gymnast.getImagePath();
    else if (role == StartScoreTotalRole)
        return gymnast.getStartScore(ApparatusList::AGTotalScore);
    else if (role == FinalScoreTotalRole)
        return gymnast.getFinalScore(ApparatusList::AGTotalScore);
    else if (role == StartScoreVaultRole)
        return gymnast.getStartScore(ApparatusList::AWVault);
    else if (role == FinalScoreVaultRole)
        return gymnast.getFinalScore(ApparatusList::AWVault);
    else if (role == StartScoreUnBarsRole)
        return gymnast.getStartScore(ApparatusList::AWUnevenBars);
    else if (role == FinalScoreUnBarsRole)
        return gymnast.getFinalScore(ApparatusList::AWUnevenBars);
    else if (role == StartScoreBalBeamRole)
        return gymnast.getStartScore(ApparatusList::AWBalanceBeam);
    else if (role == FinalScoreBalBeamRole)
        return gymnast.getFinalScore(ApparatusList::AWBalanceBeam);
    else if (role == StartScoreFloorRole)
        return gymnast.getStartScore(ApparatusList::AWFloor);
    else if (role == FinalScoreFloorRole)
        return gymnast.getFinalScore(ApparatusList::AWFloor);

    return QVariant();
}

QHash<int, QByteArray> AllroundWomenDataModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[RankRole             ] = "Rank";
    roles[NameFullRole         ] = "NameFull";
    roles[FlagImageRole        ] = "FlagImage";
    roles[StartScoreTotalRole  ] = "StartScore_Total";
    roles[FinalScoreTotalRole  ] = "FinalScore_Total";
    roles[StartScoreFloorRole  ] = "StartScore_Floor";
    roles[FinalScoreFloorRole  ] = "FinalScore_Floor";
    roles[StartScoreUnBarsRole ] = "StartScore_UnBars";
    roles[FinalScoreUnBarsRole ] = "FinalScore_UnBars";
    roles[StartScoreBalBeamRole] = "StartScore_BalBeam";
    roles[FinalScoreBalBeamRole] = "FinalScore_BalBeam";
    roles[StartScoreVaultRole  ] = "StartScore_Vault";
    roles[FinalScoreVaultRole  ] = "FinalScore_Vault";


    return roles;
}

QModelIndex AllroundWomenDataModel::indexFromItem(const AthleteData* item) const
{
    Q_ASSERT(item);
    for(int row=0; row<m_rankingList.size(); ++row)
    {
        if(m_rankingList.at(row) == (*item)) return index(row);
    }
    return QModelIndex();
}

AthleteData *AllroundWomenDataModel::GetItem(QString& nameFull)
{
    QList<AthleteData>::const_iterator iter;
    for (iter = m_rankingList.constBegin(); iter != m_rankingList.constEnd(); ++iter)
    {
        if ((iter)->getNameFull() == nameFull)
            return (AthleteData*)iter.i->v;
    }

    return NULL;
}
