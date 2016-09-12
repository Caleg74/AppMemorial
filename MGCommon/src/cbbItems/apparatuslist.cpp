#include "apparatuslist.h"
#include <QQmlContext>
#include "dbinterface.h"

// Static membe rinitialization
ApparatusList* ApparatusList::sm_pInstance = NULL;

ApparatusList::ApparatusList()
    : m_cCbbModel()
{
}

ApparatusList* ApparatusList::Instance()
{
    if (sm_pInstance == NULL)
    {
       sm_pInstance = new ApparatusList();
    }

    return sm_pInstance;
}

void ApparatusList::Init(QQmlApplicationEngine &p_qEngine)
{
    QQmlContext* pComboContext = p_qEngine.rootContext();
    pComboContext->setContextProperty("apparatusModel", &m_cCbbModel);

    // move after mySQL read-out
    RetrieveFromDb();
}

void ApparatusList::RetrieveFromDb()
{
    QStringList tmp;
    dbInterface::Instance()->getApparatusList(&tmp);

    for (int i = 0; i < tmp.size(); ++i)
    {
        QStringList items = tmp.at(i).split(',');

        if (items.count() == 4) // 4 items retrieved
        {
            m_ApparatusList << new ApparatusData(items.at(0).toInt(),   // id
                                                 items.at(1),           // name_it
                                                 items.at(2),           // name_en
                                                 items.at(3));           // gender

            if ((items.at(2) == "Floor") && (items.at(3) == "M")) m_aiEnumToIdMen[AMFloor] = items.at(0).toInt();
            else if ((items.at(2) == "Pommel horse") && (items.at(3) == "M")) m_aiEnumToIdMen[AMPommelHores] = items.at(0).toInt();
            else if ((items.at(2) == "Rings") && (items.at(3) == "M")) m_aiEnumToIdMen[AMRings] = items.at(0).toInt();
            else if ((items.at(2) == "Vault") && (items.at(3) == "M")) m_aiEnumToIdMen[AMVault] = items.at(0).toInt();
            else if ((items.at(2) == "Parallel bars") && (items.at(3) == "M")) m_aiEnumToIdMen[AMParallelBars] = items.at(0).toInt();
            else if ((items.at(2) == "Horizontal bar") && (items.at(3) == "M")) m_aiEnumToIdMen[AMHorizontalBar] = items.at(0).toInt();
            else if ((items.at(2) == "Vault") && (items.at(3) == "F")) m_aiEnumToIdWomen[AWVault] = items.at(0).toInt();
            else if ((items.at(2) == "Uneven bars") && (items.at(3) == "F")) m_aiEnumToIdWomen[AWUnevenBars] = items.at(0).toInt();
            else if ((items.at(2) == "Balance beam") && (items.at(3) == "F")) m_aiEnumToIdWomen[AWBalanceBeam] = items.at(0).toInt();
            else if ((items.at(2) == "Floor") && (items.at(3) == "F")) m_aiEnumToIdWomen[AWFloor] = items.at(0).toInt();

        }
        else
        {
            qCritical() << "RetrieveFromDb(): items count incorrect";
        }
    }
}

void ApparatusList::FillComboList(QString p_strGender)
{
    QStringList tmp;

    // which content is
    tmp << "Attrezzo..";

    for (int i=0; i<m_ApparatusList.count(); i++)
    {
        if (m_ApparatusList.at(i)->getGender() == p_strGender)
        {
            tmp << m_ApparatusList.at(i)->getName(ApparatusData::ALangIt);
        }
    }

    m_cCbbModel.setComboList(tmp);
}

int ApparatusList::getApparatusId(EApparatusMen p_eApparatusMen)
{
    return m_aiEnumToIdMen[p_eApparatusMen];
}

int ApparatusList::getApparatusId(EApparatusWomen p_eApparatusWomen)
{
    return m_aiEnumToIdWomen[p_eApparatusWomen];
}
