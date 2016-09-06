#include "savescore.h"
#include <qdebug.h>
#include "messagebox.h"
#include "dbinterface.h"


// static member initialization
SaveScore* SaveScore::sm_instance = NULL;


SaveScore::SaveScore(QObject* parent)
    : QObject(parent)
{

}

SaveScore* SaveScore::Instance()
{
    if (sm_instance == NULL)
    {
        sm_instance = new SaveScore();
    }

    return sm_instance;
}

void SaveScore::onSaveScore(QString p_strGymnastFullTxt,
                         QString p_strApparatus,
                         QString p_strStartScore,
                         QString p_strFinalScore)
{
    qDebug() << "onSaveScore(): " << p_strGymnastFullTxt <<  ", "
                << p_strApparatus <<  ", "
                << p_strStartScore <<  ", "
                << p_strFinalScore;

    QString strErr = "";
    bool bConvStartScoreOk = false;
    float fStartScore = CheckStartScore(p_strStartScore, &bConvStartScoreOk);

    if (!bConvStartScoreOk)
    {
        strErr = "Nota di partenza non é tra 0 e 10";
    }

    bool bConvFinalScoreOk = false;
    float fFinalScore = CheckFinalScore(p_strFinalScore, &bConvFinalScoreOk);

    if (!bConvFinalScoreOk)
    {
        if (!strErr.isEmpty())
            strErr += "\n";

        strErr += "Nota finale non é tra 0 e 20";
    }

    // save it to DB
    SendToDb(p_strGymnastFullTxt, p_strApparatus, fStartScore, fFinalScore);

    // Show it to the user
    if ((!bConvStartScoreOk) || (!bConvFinalScoreOk))
    {
        MessageBox cMsgBox;
        cMsgBox.SetTitle("Warning");
        cMsgBox.SetText(strErr);
        cMsgBox.Show();
    }
}

float SaveScore::CheckStartScore(QString p_strInputVal, bool* bOk)
{
    float fScore = p_strInputVal.toFloat(bOk);
    if (*bOk)
    {
        if ((fScore < 0.0) || (fScore > 10.0))
        {
            *bOk = false;
        }
    }

    return fScore;
}

float SaveScore::CheckFinalScore(QString p_strInputVal, bool* bOk)
{
    float fScore = p_strInputVal.toFloat(bOk);
    if (*bOk)
    {
        if ((fScore < 0.0) || (fScore > 20.0))
        {
            *bOk = false;
        }
    }

    return fScore;
}

void SaveScore::SendToDb(QString& p_strGymnastFullTxt,
                         QString& p_strApparatus,
                         float p_fStartScore,
                         float p_fFinalScore)
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
        dbInterface::Instance()->updateScore(iEventId, iAthleteId,
                                         iApparatusId, p_fStartScore, p_fFinalScore);
    }
    else
    {
        // insert a new one
        dbInterface::Instance()->setNewScore(iEventId, iAthleteId,
                                         iApparatusId, p_fStartScore, p_fFinalScore);
    }
}
