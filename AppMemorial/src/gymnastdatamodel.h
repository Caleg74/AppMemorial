#ifndef GYMNASTDATAMODEL_H
#define GYMNASTDATAMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include "gymnastdata.h"

class GymnastDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum GymnastRoles {
        FirsNameRole = Qt::UserRole + 1,
        LastNameRole,
        CountryRole,
        SexRole
    };

    GymnastDataModel(QObject *parent = 0);

    void addGymnast(const GymnastData &gymnast);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<GymnastData> m_gymnastList;
};

#endif // GYMNASTDATAMODEL_H
