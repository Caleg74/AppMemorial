#include "allroundmensortfilterproxymodel.h"
#include "allroundmendatamodel.h"
#include <QtCore>

AllroundMenSortFilterProxyModel::AllroundMenSortFilterProxyModel(QObject *parent)
 : QSortFilterProxyModel(parent)
{

}

bool AllroundMenSortFilterProxyModel::lessThan(const QModelIndex &left,
                                           const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left, AllroundMenDataModel::RankRole);
    QVariant rightData = sourceModel()->data(right, AllroundMenDataModel::RankRole);

//    qDebug() << "leftData: "  << leftData.toString();
//    qDebug() << "rightData: " << rightData.toString();
//    qDebug() << "Compare = " << (QString::compare(leftData.toString(), rightData.toString(), Qt::CaseInsensitive)<0);

   return leftData.toInt() < rightData.toInt();
}

