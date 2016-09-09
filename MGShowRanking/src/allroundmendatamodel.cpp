#include "allroundmendatamodel.h"
#include "dbinterface.h"
#include <QAbstractItemModel>
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
    RetrieveGymnastList();;
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
        AllroundMenData cNewGymnast(p_strGymnList.at(i)[0], p_strGymnList.at(i)[1],
                p_strGymnList.at(i)[2], p_strGymnList.at(i)[3]);

        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_rankingList << cNewGymnast;
        endInsertRows();
    }
}

void AllroundMenDataModel::addItem(QString firstName,
                               QString lastName,
                               QString country,
                               QString sex)
{

    int iNationId = dbInterface::Instance()->getNationId(country);

    AllroundMenData cNewGymnast(firstName, lastName, country, sex);

    // add it to the database
    dbInterface::Instance()->insertGymnast(firstName, lastName, sex, iNationId);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_rankingList << cNewGymnast;
    endInsertRows();
}

void AllroundMenDataModel::removeItem(QString firstName, QString lastName)
{
    AllroundMenData* pItem = GetItem(firstName, lastName);

    QModelIndex pIndex = indexFromItem(pItem);

    // add it to the database
    dbInterface::Instance()->deleteGymnast(firstName, lastName);

    beginRemoveRows(QModelIndex(), pIndex.row(), pIndex.row());
    m_rankingList.removeAt(pIndex.row());
    endRemoveRows();
}

int AllroundMenDataModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_rankingList.count();
}

QVariant AllroundMenDataModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_rankingList.count())
        return QVariant();

    const AllroundMenData &gymnast = m_rankingList[index.row()];
    if (role == FirstNameRole)
        return gymnast.FirstName();
    else if (role == LastNameRole)
        return gymnast.LastName();
    else if (role == CountryRole)
        return gymnast.Country();
    else if (role == SexRole)
        return gymnast.Sex();
    return QVariant();
}

QHash<int, QByteArray> AllroundMenDataModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FirstNameRole] = "FirstName";
    roles[LastNameRole]  = "LastName";
    roles[CountryRole]   = "Country";
    roles[SexRole]       = "Sex";

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

AllroundMenData* AllroundMenDataModel::GetItem(QString& firstName, QString& lastName)
{
    QList<AllroundMenData>::const_iterator iter;
    for (iter = m_rankingList.constBegin(); iter != m_rankingList.constEnd(); ++iter)
    {
        if (((iter)->FirstName() == firstName) && ((iter)->LastName() == lastName))
            return (AllroundMenData*)iter.i->v;
    }

    return NULL;
}
