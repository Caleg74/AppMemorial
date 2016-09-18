#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H

#include <QTimer>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include "sortfilterproxymodel.h"
#include "comboboxmodel.h"
#include "allroundmendatamodel.h"
#include "allroundwomendatamodel.h"
#include "singlemwdatamodel.h"

class CoreApplication : public QObject
{
    Q_OBJECT
public:
    explicit CoreApplication(QObject *parent = 0);

    virtual ~CoreApplication();

    /** Initializes the core application components */
    void Init(QQmlApplicationEngine &p_qEngine);

    /** Connectes all UI signals */
    void Connect();

signals:

public slots:
    void onWindowLoaded();

    void onWindowClosing(QQuickCloseEvent *p_event);

    void updateScores();

    void onApparatusMChanged(QString p_currentTxt);

    void onApparatusWChanged(QString p_currentTxt);

private:

    AllroundWomenDataModel* m_pGymWomenModel;
    AllroundMenDataModel*   m_pGymMenModel;
    SingleMWDataModel*      m_pSingleMModel;
    SingleMWDataModel*      m_pSingleWModel;

    QQmlApplicationEngine* m_pAppEngine;

    SortFilterProxyModel* m_qSortMProxy;
    SortFilterProxyModel* m_qSortWProxy;
    SortFilterProxyModel* m_qSortSingleMProxy;
    SortFilterProxyModel* m_qSortSingleWProxy;

    ComboBoxModel m_cbbApparatusMen;
    ComboBoxModel m_cbbApparatusWomen;

    QTimer* m_updateTimer;
};

#endif // COREAPPLICATION_H
