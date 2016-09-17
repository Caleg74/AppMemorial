#ifndef ALLROUNDMENSORTFILTERPROXYMODEL_H
#define ALLROUNDMENSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class SortFilterProxyModel : public QSortFilterProxyModel
{
public:
    SortFilterProxyModel(QObject *parent = NULL);

    bool lessThan(const QModelIndex &left,
                  const QModelIndex &right) const;

protected:
    virtual bool filterAcceptsRow(int sourceRow,
              const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
};

#endif // GYMNASTSORTFILTERPROXYMODEL_H
