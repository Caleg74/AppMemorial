#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "gymnastsortfilterproxymodel.h"

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

        void onSortClicked();
private:
    QQmlApplicationEngine* m_pAppEngine;

    GymnastSortFilterProxyModel* m_qSortProxy;
};

#endif // COREAPPLICATION_H
