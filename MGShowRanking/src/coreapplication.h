#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "allroundmensortfilterproxymodel.h"

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

    AllroundMenSortFilterProxyModel* m_qSortProxy;
};

#endif // COREAPPLICATION_H
