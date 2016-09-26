#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "gymnastsortfilterproxymodel.h"
#include "comboboxmodel.h"
#include "createpdf.h"

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

public slots:
    void onGymnastChanged(QString p_currentTxt);

private:
    QQmlApplicationEngine* m_pAppEngine;

    GymnastSortFilterProxyModel* m_qSortProxyGymnast;
    GymnastSortFilterProxyModel* m_qSortProxySelectedGymnast;

    ComboBoxModel m_pApparatusCbbModel;

    CreatePdf m_cPdf;
};

#endif // COREAPPLICATION_H
