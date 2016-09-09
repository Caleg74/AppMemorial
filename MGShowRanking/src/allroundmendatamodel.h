#ifndef ALLROUNDMENDATAMODEL_H
#define ALLROUNDMENDATAMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "allroundmendata.h"

class AllroundMenDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum GymnastRoles {
        FirstNameRole = Qt::UserRole + 1,
        LastNameRole,
        CountryRole,
        SexRole
    };

    /** Singleton */
    static AllroundMenDataModel* Instance();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

//    bool insertRow(int row, const QModelIndex & parent = QModelIndex());


public slots:

    void addItem(QString firstName,
                 QString lastName,
                 QString country,
                 QString sex);

    void removeItem(QString firstName, QString lastName);

protected:
    QHash<int, QByteArray> roleNames() const;

private:

    AllroundMenData* GetItem(QString& firstName, QString& lastName);

    QModelIndex indexFromItem( const AllroundMenData* item) const;

    AllroundMenDataModel(QObject *parent = 0);

    void RetrieveGymnastList();

    static AllroundMenDataModel* sm_pInstance;   ///< Singleton

    QList<AllroundMenData> m_rankingList;
};

#endif // ALLROUNDMENDATAMODEL_H
