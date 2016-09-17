#ifndef SINGLEMWDATAMODEL_H
#define SINGLEMWDATAMODEL_H

#include "gymnastdatamodel.h"
#include "singlemwdata.h"
#include "apparatuslist.h"

class SingleMWDataModel : public GymnastDataModel
{
    Q_OBJECT
public:
    enum AllroundWRoles {
        FinalScoreTotalRole = LastGeneralRole,
        StartScoreSingleMW,
        FinalScoreSingleMW
     };

    enum SingleGender
    {
        SG_Unknown,
        SG_Men,
        SG_Women
    };

    SingleMWDataModel(const QString& p_strGender, QObject *parent = 0);

    ~SingleMWDataModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

//    bool insertRow(int row, const QModelIndex & parent = QModelIndex());

    void setApparatus(ApparatusList::EApparatusMen p_eAppMen);

public slots:

    void updateScores();

//    void addItem(QString nameFull);

//    void removeItem(QString nameFull);

protected:
    QHash<int, QByteArray> roleNames() const;

private:

    SingleMWData* GetItem(QString& nameFull);

    QModelIndex indexFromItem( const SingleMWData* item) const;

    void RetrieveGymnastList();

    SingleGender m_eGender;

    ApparatusList::EApparatusMen m_eApparatus;

    QList<SingleMWData> m_rankingList;
};

#endif // SINGLEMWDATAMODEL_H
