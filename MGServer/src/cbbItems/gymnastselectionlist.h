#ifndef GYMNASTSELECTIONLIST_H
#define GYMNASTSELECTIONLIST_H

#include "comboboxmodel.h"
#include <QQmlApplicationEngine>

class GymnastSelectionList
{
public:
    GymnastSelectionList();

    /** Initializes the core application components */
    void Init(QQmlApplicationEngine &p_qEngine);

    void FillList();

private:

    ComboBoxModel m_cCbbModel;
};

#endif // GYMNASTSELECTIONLIST_H
