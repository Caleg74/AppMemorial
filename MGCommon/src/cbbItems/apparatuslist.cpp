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
    FillList();
}

void ApparatusList::FillList()
{
    QStringList tmp;
    dbInterface::Instance()->getApparatusList(&tmp);

    m_cCbbModel.setComboList(tmp);
}

