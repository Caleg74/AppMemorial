#ifndef ALLROUNDMENDATAMODEL_H
#define ALLROUNDMENDATAMODEL_H

#include "gymnastdatamodel.h"
#include "athletedata.h"

class AllroundMenDataModel : public GymnastDataModel
{
    Q_OBJECT
public:
    enum AllroundMRoles {
        StartScoreTotalRole = LastGeneralRole,
        FinalScoreTotalRole,
        StartScoreFloorRole,
        FinalScoreFloorRole,
        FinalApparatusFloorRole,
        LatestScoreFloorRole,
        StartScorePHorseRole,
        FinalScorePHorseRole,
        FinalApparatusPHorseRole,
        LatestScorePHorseRole,
        StartScoreRingsRole,
        FinalScoreRingsRole,
        FinalApparatusRingsRole,
        LatestScoreRingsRole,
        StartScoreVaultRole,
        FinalScoreVaultRole,
        FinalApparatusVaultRole,
        LatestScoreVaultRole,
        StartScorePBarsRole,
        FinalScorePBarsRole,
        FinalApparatusPBarsRole,
        LatestScorePBarsRole,
        StartScoreHBarRole,
        FinalScoreHBarRole,
        FinalApparatusHBarRole,
        LatestScoreHBarRole,
    };

    AllroundMenDataModel(QObject *parent = 0);

    ~AllroundMenDataModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

//    bool insertRow(int row, const QModelIndex & parent = QModelIndex());


public slots:

    void updateScores();

//    void addItem(QString nameFull);

//    void removeItem(QString nameFull);

protected:
    QHash<int, QByteArray> roleNames() const;

    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
private:

    AthleteData* GetItem(QString& nameFull);

    QModelIndex indexFromItem( const AthleteData* item) const;

    void RetrieveGymnastList();

    QList<AthleteData> m_rankingList;
};

#endif // ALLROUNDMENDATAMODEL_H
