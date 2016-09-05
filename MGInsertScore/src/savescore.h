#ifndef SAVESCORE_H
#define SAVESCORE_H

#include <QObject>

class SaveScore : public QObject
{
    Q_OBJECT
public:
    static SaveScore* Instance();

public slots:
    void onSaveScore(QString p_strGymnastFullTxt,
                     QString p_strApparatus,
                     QString p_strStartScore,
                     QString p_strFinalScore);

private:
    SaveScore(QObject* parent = NULL);

    float CheckStartScore(QString p_strInputVal, bool* bOk);

    float CheckFinalScore(QString p_strInputVal, bool* bOk);

    void SendToDb(QString& p_strGymnastFullTxt,
                  QString& p_strApparatus,
                  float p_fStartScore,
                  float p_fFinalScore);

    static SaveScore* sm_instance;

    QObject* m_qMsgDialog;  ///< for pop-up
};

#endif // SAVESCORE_H
