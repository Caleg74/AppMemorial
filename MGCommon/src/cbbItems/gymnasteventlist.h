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

    void FillList();

private:

    GymnastEventList();

    static GymnastEventList* sm_pInstance;

    ComboBoxModel m_cCbbModel;
};

#endif // GYMNASTEVENTLIST_H
