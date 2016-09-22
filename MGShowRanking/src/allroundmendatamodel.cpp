#include "allroundmendatamodel.h"
#include "dbinterface.h"
#include "sortfilterproxymodel.h"

//**** STATIC MEMBER INITIALIZATION *********************

AllroundMenDataModel::AllroundMenDataModel(QObject *parent)
    : GymnastDataModel(parent)
{
    RetrieveGymnastList();
}

AllroundMenDataModel::~AllroundMenDataModel()
{
    m_rankingList.clear();
}

void AllroundMenDataModel::RetrieveGymnastList()
{
    QString firstName;
    QString lastName;
    QString countryFile;
    int athleteId;

    QList<QStringList> p_strGymnList;
    dbInterface::Instance()->retrieveRegisteredGymnastList(p_strGymnList, dbIfaceBase::NI_IsoName);

    for (int i = 0; i < p_strGymnList.size();i++)
    {
        if (p_strGymnList.at(i)[3] == "M")  // only Men ranking here
        {
            firstName = p_strGymnList.at(i)[0];
            lastName = p_strGymnList.at(i)[1];
            countryFile = "qrc:/flags/" + (p_strGymnList.at(i)[2]).toLower() + ".svg";
            athleteId = dbInterface::Instance()->getGymnastId(firstName, lastName);

            AllroundMenData cAllroundMen(athleteId, firstName
                    + " " + lastName + "  ", countryFile);

            beginInsertRows(QModelIndex(), rowCount(), rowCount());
            m_rankingList << cAllroundMen;
            endInsertRows();
        }
    }
}

void AllroundMenDataModel::updateScores()
{
    QList<AllroundMenData>::iterator iter;

    for (iter = m_rankingList.begin(); iter != m_rankingList.end(); ++iter)
    {
        for (int apparatus = 0; apparatus < ApparatusList::AMApparatusMax; apparatus++)
        {
            int iAthleteId = iter->getAthleteId();
            int iAppId = ApparatusList::Instance()->getApparatusId((ApparatusList::EApparatusMen)apparatus);
            float fStartScore = dbInterface::Instance()->getStartScore(iAthleteId, iAppId);
            float fFinalScore = dbInterface::Instance()->getFinalScore(iAthleteId, iAppId);

//            float fFinalRandom = (float)(qrand() % ((15000 + 1) - 10000) + 10000) / 1000;
//            float fStartRandom = fFinalRandom - 10;
            iter->setFinalScore((ApparatusList::EApparatusMen)apparatus, fFinalScore);
            iter->setStartScore((ApparatusList::EApparatusMen)apparatus, fStartScore);
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


//void AllroundMenDataModel::addItem(QString nameFull)
//{

//    int iNationId = dbInterface::Instance()->getNationId(country);

//    AllroundMenData cAllroundMen(nameFull);

//    // add it to the database
//    dbInterface::Instance()->insertGymnast(firstName, lastName, sex, iNationId);

//    beginInsertRows(QModelIndex(), rowCount(), rowCount());
//cAllroundMen    endInsertRows();
//}

//void AllroundMenDataModel::removeItem(QString nameFull)
//{
//    AllroundMenData* pItem = GetItem(firstName, lastName);

//    QModelIndex pIndex = indexFromItem(pItem);

//    // add it to the database
//    dbInterface::Instance()->deleteGymnast(firstName, lastName);

//    beginRemoveRows(QModelIndex(), pIndex.row(), pIndex.row());
//    m_rankingList.removeAt(pIndex.row());
//    endRemoveRows();
//}

int AllroundMenDataModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_rankingList.count();
}

QVariant AllroundMenDataModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_rankingList.count())
        return QVariant();

    const AllroundMenData &gymnast = m_rankingList[index.row()];
    if (role == RankRole)
        return gymnast.getRank();
    else if (role == NameFullRole)
        return gymnast.getNameFull();
    else if (role == FlagImageRole)
        return gymnast.getImagePath();
    else if (role == FinalScoreTotalRole)
        return gymnast.getTotalScore();
    else if (role == StartScoreFloorRole)
        return gymnast.getStartScore(ApparatusList::AMFloor);
    else if (role == FinalScoreFloorRole)
        return gymnast.getFinalScore(ApparatusList::AMFloor);
    else if (role == StartScorePHorseRole)
        return gymnast.getStartScore(ApparatusList::AMPommelHores);
    else if (role == FinalScorePHorseRole)
        return gymnast.getFinalScore(ApparatusList::AMPommelHores);
    else if (role == StartScoreRingsRole)
        return gymnast.getStartScore(ApparatusList::AMRings);
    else if (role == FinalScoreRingsRole)
        return gymnast.getFinalScore(ApparatusList::AMRings);
    else if (role == StartScoreVaultRole)
        return gymnast.getStartScore(ApparatusList::AMVault);
    else if (role == FinalScoreVaultRole)
        return gymnast.getFinalScore(ApparatusList::AMVault);
    else if (role == StartScorePBarsRole)
        return gymnast.getStartScore(ApparatusList::AMParallelBars);
    else if (role == FinalScorePBarsRole)
        return gymnast.getFinalScore(ApparatusList::AMParallelBars);
    else if (role == StartScoreHbarRole)
        return gymnast.getStartScore(ApparatusList::AMHorizontalBar);
    else if (role == FinalScoreHbarRole)
        return gymnast.getFinalScore(ApparatusList::AMHorizontalBar);

    return QVariant();
}

QHash<int, QByteArray> AllroundMenDataModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[RankRole            ] = "Rank";
    roles[NameFullRole        ] = "NameFull";
    roles[FlagImageRole       ] = "FlagImage";
    roles[FinalScoreTotalRole ] = "FinalScore_Total";
    roles[StartScoreFloorRole ] = "StartScore_Floor";
    roles[FinalScoreFloorRole ] = "FinalScore_Floor";
    roles[StartScorePHorseRole] = "StartScore_PHorse";
    roles[FinalScorePHorseRole] = "FinalScore_PHorse";
    roles[StartScoreRingsRole ] = "StartScore_Rings";
    roles[FinalScoreRingsRole ] = "FinalScore_Rings";
    roles[StartScoreVaultRole ] = "StartScore_Vault";
    roles[FinalScoreVaultRole ] = "FinalScore_Vault";
    roles[StartScorePBarsRole ] = "StartScore_ParallelBars";
    roles[FinalScorePBarsRole ] = "FinalScore_ParallelBars";
    roles[StartScoreHbarRole  ] = "StartScore_HBar";
    roles[FinalScoreHbarRole  ] = "FinalScore_HBar";

    return roles;
}

QModelIndex AllroundMenDataModel::indexFromItem(const AllroundMenData* item) const
{
    Q_ASSERT(item);
    for(int row=0; row<m_rankingList.size(); ++row)
    {
        if(m_rankingList.at(row) == (*item)) return index(row);
    }
    return QModelIndex();
}

AllroundMenData* AllroundMenDataModel::GetItem(QString& nameFull)
{
    QList<AllroundMenData>::const_iterator iter;
    for (iter = m_rankingList.constBegin(); iter != m_rankingList.constEnd(); ++iter)
    {
        if ((iter)->getNameFull() == nameFull)
            return (AllroundMenData*)iter.i->v;
    }

    return NULL;
}

bool AllroundMenDataModel::filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const
{
    Q_UNUSED(source_row);
    Q_UNUSED(source_parent);

    return true;
}
