#include "singlemwdatamodel.h"
#include <QDebug>
#include "dbinterface.h"
#include "sortfilterproxymodel.h"

//**** STATIC MEMBER INITIALIZATION *********************

SingleMWDataModel::SingleMWDataModel(const QString& p_strGender, QObject *parent)
    : GymnastDataModel(parent)
{
    if (p_strGender == "M")
    {
        m_eGender = SG_Men;
    }
    else if (p_strGender == "F")
    {
        m_eGender = SG_Women;
    }
    else
    {
        m_eGender = SG_Unknown;
        qCritical() << "Wrong gender string";
    }

    RetrieveGymnastList();

}

SingleMWDataModel::~SingleMWDataModel()
{
    m_rankingList.clear();
}

void SingleMWDataModel::setApparatus(ApparatusList::EApparatusMen p_eAppMen)
{
    m_iApparatus = (int)p_eAppMen;
}

void SingleMWDataModel::setApparatus(ApparatusList::EApparatusWomen p_eAppWomen)
{
    m_iApparatus = (int)p_eAppWomen;
}

void SingleMWDataModel::RetrieveGymnastList()
{
    QString firstName;
    QString lastName;
    QString countryFile;
    int athleteId;

    QList<QStringList> p_strGymnList;
    dbInterface::Instance()->retrieveRegisteredGymnastList(p_strGymnList);

    QString strGender = m_eGender == SG_Men ? "M" : "F";
    for (int i = 0; i < p_strGymnList.size();i++)
    {
        if (p_strGymnList.at(i)[3] == strGender)  // only Men ranking here
        {
            firstName = p_strGymnList.at(i)[0];
            lastName = p_strGymnList.at(i)[1];
            countryFile = "qrc:/flags/" + (p_strGymnList.at(i)[2]).toLower() + ".svg";
            athleteId = dbInterface::Instance()->getGymnastId(firstName, lastName);

            SingleMWData cSingleMW(athleteId, firstName
                    + " " + lastName + "  ", countryFile);

            beginInsertRows(QModelIndex(), rowCount(), rowCount());
            m_rankingList << cSingleMW;
            endInsertRows();
        }
    }
}

void SingleMWDataModel::updateScores()
{
    QList<SingleMWData>::iterator iter;


    int iAppId;
    if (m_eGender == SG_Men)
        iAppId= ApparatusList::Instance()->getApparatusId((ApparatusList::EApparatusMen)m_iApparatus);
    else
        iAppId= ApparatusList::Instance()->getApparatusId((ApparatusList::EApparatusWomen)m_iApparatus);

    for (iter = m_rankingList.begin(); iter != m_rankingList.end(); ++iter)
    {
        int iAthleteId = iter->getAthleteId();
        float fStartScore = dbInterface::Instance()->getStartScore(iAthleteId, iAppId);
        float fFinalScore = dbInterface::Instance()->getFinalScore(iAthleteId, iAppId);
        int iForceScore   = dbInterface::Instance()->getForceScore(iAthleteId, iAppId);

        iter->setFinalScore(fFinalScore);
        iter->setStartScore(fStartScore);
        iter->setForceScore(iForceScore);
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

int SingleMWDataModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_rankingList.count();
}

QVariant SingleMWDataModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_rankingList.count())
        return QVariant();

    const SingleMWData &gymnast = m_rankingList[index.row()];
    if (role == RankRole)
        return gymnast.getRank();
    else if (role == NameFullRole)
        return gymnast.getNameFull();
    else if (role == FlagImageRole)
        return gymnast.getImagePath();
    else if (role == StartScoreSingleMW)
        return gymnast.getStartScore();
    else if (role == FinalScoreSingleMW)
        return gymnast.getFinalScore();


    return QVariant();
}

QHash<int, QByteArray> SingleMWDataModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[RankRole             ] = "Rank";
    roles[NameFullRole         ] = "NameFull";
    roles[FlagImageRole        ] = "FlagImage";
    roles[StartScoreSingleMW   ] = "StartScore_SingleMW";
    roles[FinalScoreSingleMW   ] = "FinalScore_SingleMW";

    return roles;
}

QModelIndex SingleMWDataModel::indexFromItem(const SingleMWData* item) const
{
    Q_ASSERT(item);
    for(int row=0; row<m_rankingList.size(); ++row)
    {
        if(m_rankingList.at(row) == (*item)) return index(row);
    }
    return QModelIndex();
}

SingleMWData* SingleMWDataModel::GetItem(QString& nameFull)
{
    QList<SingleMWData>::const_iterator iter;
    for (iter = m_rankingList.constBegin(); iter != m_rankingList.constEnd(); ++iter)
    {
        if ((iter)->getNameFull() == nameFull)
            return (SingleMWData*)iter.i->v;
    }

    return NULL;
}
