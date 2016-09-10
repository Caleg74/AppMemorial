#include "allroundmendatamodel.h"
#include "dbinterface.h"
#include <QAbstractItemModel>
#include <QTimer>
#include "allroundmensortfilterproxymodel.h"

//**** STATIC MEMBER INITIALIZATION *********************
AllroundMenDataModel* AllroundMenDataModel::sm_pInstance = NULL;


//*******************************************************

AllroundMenDataModel* AllroundMenDataModel::Instance()
{
    if (sm_pInstance == NULL)
    {
        sm_pInstance = new AllroundMenDataModel();

    }

    return sm_pInstance;
}

AllroundMenDataModel::AllroundMenDataModel(QObject *parent)
    : QAbstractListModel(parent)
{
    RetrieveGymnastList();

}

void AllroundMenDataModel::RetrieveGymnastList()
{
    QString firstName;
    QString lastName;
    QString country;
    QString sex;

    QList<QStringList> p_strGymnList;
    dbInterface::Instance()->retrieveRegisteredGymnastList(p_strGymnList);

    for (int i = 0; i < p_strGymnList.size();i++)
    {
        if (p_strGymnList.at(i)[3] == "M")  // only Men ranking here
        {
            AllroundMenData cAllroundMen(p_strGymnList.at(i)[0]
                    + ", " + p_strGymnList.at(i)[1]
                    + ", (" + p_strGymnList.at(i)[2] + ")");

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
        for (int apparatus = 0; apparatus < AllroundMenData::AApparatusMax; apparatus++)
        {
            float fFinalRandom = (float)(qrand() % ((15000 + 1) - 10000) + 10000) / 1000;
            float fStartRandom = fFinalRandom - 10;
            iter->setFinalScore((AllroundMenData::EApparatus)apparatus, fFinalRandom);
            iter->setStartScore((AllroundMenData::EApparatus)apparatus, fStartRandom);
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
    else if (role == FinalScoreTotalRole)
        return gymnast.getTotalScore();
    else if (role == StartScoreFloorRole)
        return gymnast.getStartScore(AllroundMenData::AFloor);
    else if (role == FinalScoreFloorRole)
        return gymnast.getFinalScore(AllroundMenData::AFloor);
    else if (role == StartScorePHorseRole)
        return gymnast.getStartScore(AllroundMenData::APommelHores);
    else if (role == FinalScorePHorseRole)
        return gymnast.getFinalScore(AllroundMenData::APommelHores);
    else if (role == StartScoreRingsRole)
        return gymnast.getStartScore(AllroundMenData::ARings);
    else if (role == FinalScoreRingsRole)
        return gymnast.getFinalScore(AllroundMenData::ARings);
    else if (role == StartScoreVaultRole)
        return gymnast.getStartScore(AllroundMenData::AVault);
    else if (role == FinalScoreVaultRole)
        return gymnast.getFinalScore(AllroundMenData::AVault);
    else if (role == StartScorePBarsRole)
        return gymnast.getStartScore(AllroundMenData::AParallelBars);
    else if (role == FinalScorePBarsRole)
        return gymnast.getFinalScore(AllroundMenData::AParallelBars);
    else if (role == StartScoreHbarRole)
        return gymnast.getStartScore(AllroundMenData::AHorizontalBar);
    else if (role == FinalScoreHbarRole)
        return gymnast.getFinalScore(AllroundMenData::AHorizontalBar);

    return QVariant();
}

QHash<int, QByteArray> AllroundMenDataModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[RankRole            ] = "Rank";
    roles[NameFullRole        ] = "NameFull";
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
