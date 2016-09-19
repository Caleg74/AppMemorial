#ifndef SAVEFORCESCORE_H
#define SAVEFORCESCORE_H

#include <QObject>

class SaveForceScore : public QObject
{
    Q_OBJECT
public:
    static SaveForceScore* Instance();

public slots:
    void onSaveForceScore(QString p_strGymnastFullTxt,
                          QString p_strApparatus,
                          QString p_strForceScore);
private:
    SaveForceScore(QObject* parent = NULL);

    int CheckForceScore(QString p_strInputVal, bool* bOk);

    void SendToDb(QString& p_strGymnastFullTxt,
                  QString& p_strApparatus,
                  int p_iForceScore);

    static SaveForceScore* sm_instance;

    QObject* m_qMsgDialog;  ///< for pop-up
};

#endif // SAVEFORCESCORE_H
