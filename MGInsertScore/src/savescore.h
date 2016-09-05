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

    static SaveScore* sm_instance;

    QObject* m_qMsgDialog;  ///< for pop-up
};

#endif // SAVESCORE_H
