#include "saveforcescore.h"
#include <qdebug.h>
#include "messagebox.h"
#include "dbinterface.h"


// static member initialization
SaveForceScore* SaveForceScore::sm_instance = NULL;


SaveForceScore::SaveForceScore(QObject* parent)
    : QObject(parent)
{

}

SaveForceScore* SaveForceScore::Instance()
{
    if (sm_instance == NULL)
    {
        sm_instance = new SaveForceScore();
    }

    return sm_instance;
}

void SaveForceScore::onSaveForceScore(QString p_strGymnastFullTxt,
                         QString p_strApparatus,
                         QString p_strForceScore)
{
    qDebug() << "onSaveForceScore(): " << p_strGymnastFullTxt <<  ", "
                << p_strApparatus <<  ", "
                << p_strForceScore;

    QString strErr = "";
    bool bConvForceScoreOk = false;
    int iForceScore = CheckForceScore(p_strForceScore, &bConvForceScoreOk);

    if (!bConvForceScoreOk)
    {
        strErr = "Valore non é tra 0 e 99";
    }

    // save it to DB
    StoreForceScore(p_strGymnastFullTxt, p_strApparatus, iForceScore);

    // Show it to the user
    if (!bConvForceScoreOk)
    {
        MessageBox cMsgBox;
        cMsgBox.SetTitle("Warning");
        cMsgBox.SetText(strErr);
        cMsgBox.Show();
    }
}

void SaveForceScore::eraseForcedScores()
{
    ResetAllForceScore();
}

int SaveForceScore::CheckForceScore(QString p_strInputVal, bool* bOk)
{
    int iScore = p_strInputVal.toInt(bOk);
    if (*bOk)
    {
        if ((iScore < 0) || (iScore > 99))
        {
            *bOk = false;
        }
    }

    return iScore;
}


void SaveForceScore::StoreForceScore(QString& p_strGymnastFullTxt,
                         QString& p_strApparatus,
                         int p_iForceScore)
{
    QStringList strSplit = p_strGymnastFullTxt.split(',');
    if (strSplit.count() < 2)
    {
        qCritical() << "SendToDb(): first/last name formatting error";
        return;
    }

    QString firstName = strSplit.at(0).trimmed();
    QString lastName =  strSplit.at(1).trimmed();

    int iAthleteId = dbInterface::Instance()->getGymnastId(firstName, lastName);
    QString strGender = dbInterface::Instance()->getGender(iAthleteId);
    int iEventId = dbInterface::Instance()->getCurrentEventId();
    int iApparatusId = dbInterface::Instance()->getApparatusId(p_strApparatus, strGender);

    bool bScorePresent = dbInterface::Instance()->isScorePresent(iEventId, iAthleteId, iApparatusId);

    if (bScorePresent)
    {
        // update existing score
        dbInterface::Instance()->updateForceScore(iEventId, iAthleteId,
                                         iApparatusId, p_iForceScore);
    }
    else
    {
        MessageBox cMsgBox;
        cMsgBox.SetTitle("Warning");
        QString strErr = "Valore non può essere assegnato se \n"
                         "non é stata data la nota.";
        cMsgBox.SetText(strErr);
        cMsgBox.Show();
    }
}

void SaveForceScore::ResetAllForceScore()
{
    int iEventId = dbInterface::Instance()->getCurrentEventId();
    dbInterface::Instance()->eraseAllForcedScore(iEventId);

    MessageBox cMsgBox;
    cMsgBox.SetTitle("Warning");
    QString strErr = "Punteggi speciali azzerati";
    cMsgBox.SetText(strErr);
    cMsgBox.Show();
}
