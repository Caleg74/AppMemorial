#include "sortfilterproxymodel.h"
#include "allroundmendatamodel.h"
#include <QtCore>
#include "singlemwdatamodel.h"

SortFilterProxyModel::SortFilterProxyModel(QObject *parent)
 : QSortFilterProxyModel(parent)
{

}

bool SortFilterProxyModel::lessThan(const QModelIndex &left,
                                           const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left, GymnastDataModel::RankRole);
    QVariant rightData = sourceModel()->data(right, GymnastDataModel::RankRole);

   return leftData.toInt() < rightData.toInt();
}

bool SortFilterProxyModel::filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const
{

    // Only the Apparatus Ranking shall not display gymnasts with a score equal 0
    if (qobject_cast<SingleMWDataModel*>(sourceModel()))
    {
        QModelIndex index0 = sourceModel()->index(source_row, 0, source_parent);
        return (sourceModel()->data(index0, SingleMWDataModel::FinalScoreSingleMW).toFloat() > 0.0);
    }
    else
    {
        return true;
    }
}
