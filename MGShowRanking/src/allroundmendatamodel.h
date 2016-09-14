#ifndef ALLROUNDMENDATAMODEL_H
#define ALLROUNDMENDATAMODEL_H

#include "allroundgymnastdatamodel.h"
#include "allroundmendata.h"

class AllroundMenDataModel : public AllroundGymnastDataModel
{
    Q_OBJECT
public:
    enum AllroundMRoles {
        FinalScoreTotalRole = LastGeneralRole,
        StartScoreFloorRole,
        FinalScoreFloorRole,
        StartScorePHorseRole,
        FinalScorePHorseRole,
        StartScoreRingsRole,
        FinalScoreRingsRole,
        StartScoreVaultRole,
        FinalScoreVaultRole,
        StartScorePBarsRole,
        FinalScorePBarsRole,
        StartScoreHbarRole,
        FinalScoreHbarRole
    };

    /** Singleton */
    static AllroundMenDataModel* Instance();

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

    AllroundMenData* GetItem(QString& nameFull);

    QModelIndex indexFromItem( const AllroundMenData* item) const;

    AllroundMenDataModel(QObject *parent = 0);

    void RetrieveGymnastList();

    static AllroundMenDataModel* sm_pInstance;   ///< Singleton

    QList<AllroundMenData> m_rankingList;
};

#endif // ALLROUNDMENDATAMODEL_H
