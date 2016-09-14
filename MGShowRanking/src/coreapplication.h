#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "allroundsortfilterproxymodel.h"

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

        void updateScores();
private:
    QQmlApplicationEngine* m_pAppEngine;

    AllroundSortFilterProxyModel* m_qSortMProxy;
    AllroundSortFilterProxyModel* m_qSortWProxy;

};

#endif // COREAPPLICATION_H
