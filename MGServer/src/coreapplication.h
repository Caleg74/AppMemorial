#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H

#include <QObject>
#include <QQmlApplicationEngine>

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

private:
    QQmlApplicationEngine* m_pAppEngine;

};

#endif // COREAPPLICATION_H
