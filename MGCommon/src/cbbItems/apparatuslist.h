#ifndef APPARATUSLIST_H
#define APPARATUSLIST_H

#include "comboboxmodel.h"
#include <QQmlApplicationEngine>
#include "apparatusdata.h"


class ApparatusList : public QObject
{
    Q_OBJECT
public:
    enum EApparatusMen
    {
        AMFloor,
        AMPommelHores,
        AMRings,
        AMVault,
        AMParallelBars,
        AMHorizontalBar,
        AMApparatusMax
    };

    enum EApparatusWomen
    {
        AWVault,
        AWUnevenBars,
        AWBalanceBeam,
        AWFloor,
        AWApparatusMax
    };

    static ApparatusList* Instance();

    /** Initializes the core application components */
    void Init(QQmlApplicationEngine &p_qEngine);

    void FillComboList(QString p_strGender);

    int getApparatusId(EApparatusMen p_eApparatusMen);
    int getApparatusId(EApparatusWomen p_eApparatusWomen);


private:

    ApparatusList();

    void RetrieveFromDb();

    static ApparatusList* sm_pInstance;

    ComboBoxModel m_cCbbModel;

    QList<ApparatusData*> m_ApparatusList;

    int m_aiEnumToIdMen[AMApparatusMax];

    int m_aiEnumToIdWomen[AWApparatusMax];

};

#endif // APPARATUSLIST_H
