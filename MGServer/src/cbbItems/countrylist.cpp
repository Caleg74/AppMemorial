#include "countrylist.h"
#include <QQmlContext>
#include "dbinterface.h"

CountryList::CountryList()
    : m_cCbbModel()
{

}

void CountryList::Init(QQmlApplicationEngine &p_qEngine)
{

    QQmlContext* pComboContext = p_qEngine.rootContext();
    pComboContext->setContextProperty("countryListModel", &m_cCbbModel);

    // move after mySQL read-out
    FillList();
}

void CountryList::FillList()
{
    QStringList tmp;

    dbInterface::Instance()->getCountriesList(&tmp);

//    tmp << "Nazione.." << "Uganda" << "Italia" << "Norvegia" << "Inghilterra" << "Romania" << "Russia" << "Brasile";
    m_cCbbModel.setComboList(tmp);
}
