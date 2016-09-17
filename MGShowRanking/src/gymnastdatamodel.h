#ifndef GYMNASTDATAMODEL_H
#define GYMNASTDATAMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "allroundmendata.h"

class GymnastDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AllroundMRoles {
        RankRole = Qt::UserRole + 1,
        NameFullRole,
        FlagImageRole,
        LastGeneralRole
    };

    GymnastDataModel(QObject *parent = 0);

    int rowCount(const QModelIndex & parent = QModelIndex()) const = 0 ;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const = 0;

protected:
    virtual QHash<int, QByteArray> roleNames() const = 0;

};

#endif // GYMNASTDATAMODEL_H
