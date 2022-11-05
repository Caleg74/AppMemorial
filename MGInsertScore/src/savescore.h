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
                     QString p_strDifficultyScore,
                     QString p_strExecutionScore,
                     QString p_strPenaltyScore,
                     QString p_strFinalScore,
                     bool p_bFinalApparatus);

private:
    SaveScore(QObject* parent = NULL);

    float CheckDifficultyScore(QString p_strInputVal, bool* bOk);
    float CheckExecutionScore(QString p_strInputVal, bool* bOk);
    float CheckPenaltyScore(QString p_strInputVal, bool* bOk);

    float CheckFinalScore(QString p_strInputVal, bool* bOk);

    void SendToDb(QString& p_strGymnastFullTxt,
                  QString& p_strApparatus,
                  float p_fDifficultyScore,
                  float p_fExecutionScore,
                  float p_fPenaltyScore,
                  float p_fFinalScore,
                  bool p_bFinalApparatus);

    static SaveScore* sm_instance;

    QObject* m_qMsgDialog;  ///< for pop-up
};

#endif // SAVESCORE_H
