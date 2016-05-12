#ifndef COUNTRYLIST_H
#define COUNTRYLIST_H

#include "comboboxmodel.h"
#include <QQmlApplicationEngine>

class CountryList
{
public:
    CountryList();

    /** Initializes the core application components */
    void Init(QQmlApplicationEngine &p_qEngine);

    void FillList();

private:
    ComboBoxModel m_cCbbModel;
};

#endif // COUNTRYLIST_H
