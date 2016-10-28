#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <comboboxmodel.h>

class CoreApplication : public QObject
{
    Q_OBJECT
public:
    explicit CoreApplication(QObject *parent = 0);

    virtual ~CoreApplication();

    /** Initializes the core application components */
    bool Init(QQmlApplicationEngine &p_qEngine);

    /** Connectes all UI signals */
    void Connect();

signals:

public slots:
    void onGymnastChanged(QString p_currentTxt);

private:
    QQmlApplicationEngine* m_pAppEngine;

    ComboBoxModel m_pApparatusCbbModel;
};

#endif // COREAPPLICATION_H
