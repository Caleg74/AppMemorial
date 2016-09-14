#ifndef ALLROUNDWOMENDATAMODEL_H
#define ALLROUNDWOMENDATAMODEL_H

#include "allroundgymnastdatamodel.h"
#include "allroundwomendata.h"

class AllroundWomenDataModel : public AllroundGymnastDataModel
{
    Q_OBJECT
public:
    enum AllroundWRoles {
        FinalScoreTotalRole = LastGeneralRole,
        StartScoreVaultRole,
        FinalScoreVaultRole,
        StartScoreUnBarsRole,
        FinalScoreUnBarsRole,
        StartScoreBalBeamRole,
        FinalScoreBalBeamRole,
        StartScoreFloorRole,
        FinalScoreFloorRole,
     };

    /** Singleton */
    static AllroundWomenDataModel* Instance();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

//    bool insertRow(int row, const QModelIndex & parent = QModelIndex());


public slots:

    void updateScores();

//    void addItem(QString nameFull);

//    void removeItem(QString nameFull);

protected:
    QHash<int, QByteArray> roleNames() const;

private:

    AllroundWomenData *GetItem(QString& nameFull);

    QModelIndex indexFromItem( const AllroundWomenData* item) const;

    AllroundWomenDataModel(QObject *parent = 0);

    void RetrieveGymnastList();

    static AllroundWomenDataModel* sm_pInstance;   ///< Singleton

    QList<AllroundWomenData> m_rankingList;
};

#endif // ALLROUNDWOMENDATAMODEL_H
