#include "gymnastsortfilterproxymodel.h"
#include "gymnastdatamodel.h"
#include <QtCore>

GymnastSortFilterProxyModel::GymnastSortFilterProxyModel(QObject *parent)
 : QSortFilterProxyModel(parent)
{

}

bool GymnastSortFilterProxyModel::lessThan(const QModelIndex &left,
                                           const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left, GymnastDataModel::FirstNameRole);
    QVariant rightData = sourceModel()->data(right, GymnastDataModel::FirstNameRole);

//    qDebug() << "leftData: "  << leftData.toString();
//    qDebug() << "rightData: " << rightData.toString();
//    qDebug() << "Compare = " << (QString::compare(leftData.toString(), rightData.toString(), Qt::CaseInsensitive)<0);

   return (QString::compare(leftData.toString(), rightData.toString(), Qt::CaseInsensitive) < 0);
}

//bool GymnastSortFilterProxyModel::filterAcceptsRow(int sourceRow,
//          const QModelIndex &sourceParent) const
//{
//    // don't think it's used...
//    return true;
//}
