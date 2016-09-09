#ifndef ALLROUNDMENSORTFILTERPROXYMODEL_H
#define ALLROUNDMENSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class AllroundMenSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    AllroundMenSortFilterProxyModel(QObject *parent = NULL);

    bool lessThan(const QModelIndex &left,
                  const QModelIndex &right) const;

//    bool filterAcceptsRow(int sourceRow,
//              const QModelIndex &sourceParent) const;
};

#endif // GYMNASTSORTFILTERPROXYMODEL_H
