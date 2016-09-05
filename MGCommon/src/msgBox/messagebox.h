#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QtCore>
#include <QQmlApplicationEngine>

class MessageBox
{
public:
    MessageBox();

    static void SetEngine(QQmlApplicationEngine *p_pAppEngine);

    void SetTitle(QString p_strTitle);

    void SetText(QString p_strText);

    void Show();

private:
    QString m_strTitle;

    QString m_strText;

    static QQmlApplicationEngine* m_pAppEngine;
};

#endif // MESSAGEBOX_H
