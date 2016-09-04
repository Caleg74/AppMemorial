#ifndef GYMNASTSELECTIONLIST_H
#define GYMNASTSELECTIONLIST_H

#include "comboboxmodel.h"
#include <QQmlApplicationEngine>

class GymnastSelectionList
{
public:

    static GymnastSelectionList* Instance();

    /** Initializes the core application components */
    void Init(QQmlApplicationEngine &p_qEngine);

    void FillList();

private:

    GymnastSelectionList();

    static GymnastSelectionList* sm_pInstance;

    ComboBoxModel m_cCbbModel;
};

#endif // GYMNASTSELECTIONLIST_H
