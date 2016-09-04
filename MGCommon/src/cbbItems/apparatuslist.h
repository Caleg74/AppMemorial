#ifndef APPARATUSLIST_H
#define APPARATUSLIST_H

#include "comboboxmodel.h"
#include <QQmlApplicationEngine>

class ApparatusList
{
public:

    static ApparatusList* Instance();

    /** Initializes the core application components */
    void Init(QQmlApplicationEngine &p_qEngine);

    void FillList();

private:

    ApparatusList();

    static ApparatusList* sm_pInstance;

    ComboBoxModel m_cCbbModel;
};

#endif // APPARATUSLIST_H
