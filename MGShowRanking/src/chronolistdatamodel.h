#ifndef CHRONOLISTDATAMODEL_H
#define CHRONOLISTDATAMODEL_H

#include "gymnastdatamodel.h"
#include "chronolistdata.h"

class ChronoListDataModel : public GymnastDataModel
{
    Q_OBJECT
public:
    enum ChronoListRoles {
        MenWomenRole = LastGeneralRole,
        NameFullRole,
        CountryRole,
        ApparatusRole,
        StartScoreRole,
        ExecutionScoreRole,
        FinalScoreRole,
        GymnastTotalScoreRole
//        RankRole
    };

    ChronoListDataModel(QObject *parent = nullptr);

    ~ChronoListDataModel();

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

    ChronoListData* GetItem(QString& nameFull);

    QModelIndex indexFromItem( const ChronoListData* item) const;

    void FillChronoList();

    QList<ChronoListData> m_chronoList;
};

#endif // CHRONOLISTDATAMODEL_H
