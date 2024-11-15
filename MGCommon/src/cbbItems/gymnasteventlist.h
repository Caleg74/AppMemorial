#ifndef GYMNASTEVENTLIST_H
#define GYMNASTEVENTLIST_H

#include "comboboxmodel.h"
#include <QQmlApplicationEngine>

class GymnastEventList
{
public:

    static GymnastEventList* Instance();

    /** Initializes the core application components */
    void Init(QQmlApplicationEngine &p_qEngine);

    /* File the gymnast List for Men or Women or both */
    void FillList(bool p_bMen, bool p_bWomen);

private:

    GymnastEventList();

    static GymnastEventList* sm_pInstance;

    ComboBoxModel m_cCbbModel;
};

#endif // GYMNASTEVENTLIST_H
