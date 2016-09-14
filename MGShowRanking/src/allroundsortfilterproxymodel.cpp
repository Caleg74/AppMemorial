#include "allroundsortfilterproxymodel.h"
#include "allroundmendatamodel.h"
#include <QtCore>

AllroundSortFilterProxyModel::AllroundSortFilterProxyModel(QObject *parent)
 : QSortFilterProxyModel(parent)
{

}

bool AllroundSortFilterProxyModel::lessThan(const QModelIndex &left,
                                           const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left, AllroundGymnastDataModel::RankRole);
    QVariant rightData = sourceModel()->data(right, AllroundGymnastDataModel::RankRole);

//    qDebug() << "leftData: "  << leftData.toString();
//    qDebug() << "rightData: " << rightData.toString();
//    qDebug() << "Compare = " << (QString::compare(leftData.toString(), rightData.toString(), Qt::CaseInsensitive)<0);

   return leftData.toInt() < rightData.toInt();
}

