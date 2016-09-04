#include "gymnastselectionlist.h"
#include <QQmlContext>
#include "dbinterface.h"

// Static membe rinitialization
GymnastSelectionList* GymnastSelectionList::sm_pInstance = NULL;

GymnastSelectionList::GymnastSelectionList()
    : m_cCbbModel()
{
}

GymnastSelectionList* GymnastSelectionList::Instance()
{
    if (sm_pInstance == NULL)
    {
       sm_pInstance = new GymnastSelectionList();
    }

    return sm_pInstance;
}

void GymnastSelectionList::Init(QQmlApplicationEngine &p_qEngine)
{
    QQmlContext* pComboContext = p_qEngine.rootContext();
    pComboContext->setContextProperty("gymnastRegisteredModel", &m_cCbbModel);

    // move after mySQL read-out
    FillList();
}

void GymnastSelectionList::FillList()
{
    QStringList tmp;
    dbInterface::Instance()->getRegisterdGymnastList(&tmp);

    m_cCbbModel.setComboList(tmp);
}

