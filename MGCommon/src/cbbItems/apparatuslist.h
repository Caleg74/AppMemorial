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
        AMTotalScore,
        AMFirstApparatus,
        AMFloor = AMFirstApparatus,
        AMPommelHores,
        AMRings,
        AMVault,
        AMParallelBars,
        AMHorizontalBar,
        AMApparatusMax
    };

    enum EApparatusWomen
    {
        AWTotalScore,
        AWFirstApparatus,
        AWVault = AWFirstApparatus,
        AWUnevenBars,
        AWBalanceBeam,
        AWFloor,
        AWApparatusMax
    };

    static ApparatusList* Instance();

    ~ApparatusList();

    /** Initializes the core application components */
    void Init(QQmlApplicationEngine &p_qEngine, const QString& p_strPropertyName, ComboBoxModel * const p_pCbbModel);

    void FillComboList(ComboBoxModel * const p_pCbbModel, QString p_strGender, bool p_bNoSelectionPresent = true);

    int getApparatusId(EApparatusMen p_eApparatusMen);
    int getApparatusId(EApparatusWomen p_eApparatusWomen);
    int getApparatusId(const QString& p_strApparatusName);


private:

    ApparatusList();

    void RetrieveFromDb();

    static ApparatusList* sm_pInstance;

    QList<ApparatusData*> m_ApparatusList;

    int m_aiEnumToIdMen[AMApparatusMax];

    int m_aiEnumToIdWomen[AWApparatusMax];

};

#endif // APPARATUSLIST_H
