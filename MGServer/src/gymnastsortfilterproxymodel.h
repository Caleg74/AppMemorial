#ifndef GYMNASTSORTFILTERPROXYMODEL_H
#define GYMNASTSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class GymnastSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    GymnastSortFilterProxyModel(QObject *parent = NULL);

    bool lessThan(const QModelIndex &left,
                  const QModelIndex &right) const;

//    bool filterAcceptsRow(int sourceRow,
//              const QModelIndex &sourceParent) const;
};

#endif // GYMNASTSORTFILTERPROXYMODEL_H
