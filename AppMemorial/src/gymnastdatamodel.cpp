#include "gymnastdatamodel.h"


GymnastDataModel::GymnastDataModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void GymnastDataModel::addGymnast(const GymnastData &gymnast)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_gymnastList << gymnast;
    endInsertRows();
}

int GymnastDataModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_gymnastList.count();
}

QVariant GymnastDataModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_gymnastList.count())
        return QVariant();

    const GymnastData &gymnast = m_gymnastList[index.row()];
    if (role == FirsNameRole)
        return gymnast.FirstName();
    else if (role == LastNameRole)
        return gymnast.LastName();
    else if (role == CountryRole)
        return gymnast.Country();
    else if (role == SexRole)
        return gymnast.Sex();
    return QVariant();
}

QHash<int, QByteArray> GymnastDataModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FirsNameRole] = "FirstName";
    roles[LastNameRole] = "LastName";
    roles[CountryRole]  = "Country";
    roles[SexRole]      = "Sex";

    return roles;
}

