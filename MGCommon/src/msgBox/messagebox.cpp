#include "messagebox.h"

QQmlApplicationEngine* MessageBox::m_pAppEngine = NULL;

MessageBox::MessageBox()
{

}

void MessageBox::SetEngine(QQmlApplicationEngine *p_pAppEngine)
{
    m_pAppEngine = p_pAppEngine;
}

void MessageBox::SetTitle(QString p_strTitle)
{
    m_strTitle = p_strTitle;
}

void MessageBox::SetText(QString p_strText)
{
    m_strText = p_strText;
}

void MessageBox::Show()
{
    if (m_pAppEngine != NULL)
    {
        QObject* m_qMsgDialog = m_pAppEngine->rootObjects().first()->findChild<QObject*>("messageDialog");
        if (m_qMsgDialog != NULL)
        {
            m_qMsgDialog->setProperty("title", m_strTitle);
            m_qMsgDialog->setProperty("text", m_strText);
            m_qMsgDialog->setProperty("visible", true);
        }
    }
    else
    {
        qCritical() << "Engine not set";
    }
}
