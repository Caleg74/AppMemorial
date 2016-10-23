#include "gymnasteventlist.h"
#include <QQmlContext>
#include "dbinterface.h"

// Static membe rinitialization
GymnastEventList* GymnastEventList::sm_pInstance = NULL;

GymnastEventList::GymnastEventList()
    : m_cCbbModel()
{
}

GymnastEventList* GymnastEventList::Instance()
{
    if (sm_pInstance == NULL)
    {
       sm_pInstance = new GymnastEventList();
    }

    return sm_pInstance;
}

void GymnastEventList::Init(QQmlApplicationEngine &p_qEngine)
{
    QQmlContext* pComboContext = p_qEngine.rootContext();
    pComboContext->setContextProperty("gymnastEventModel", &m_cCbbModel);

    // move after mySQL read-out
    FillList();
}

void GymnastEventList::FillList()
{
    QStringList tmp;
    dbInterface::Instance()->getEventSelectedGymnastList(&tmp);

    m_cCbbModel.setComboList(tmp);
}

