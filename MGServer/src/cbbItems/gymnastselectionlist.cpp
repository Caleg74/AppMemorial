#include "gymnastselectionlist.h"
#include <QQmlContext>
#include "dbinterface.h"

GymnastSelectionList::GymnastSelectionList()
    : m_cCbbModel()
{

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
