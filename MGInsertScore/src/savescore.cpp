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
                            QString p_strDifficultyScore,
                            QString p_strExecutionScore,
                            QString p_strPenaltyScore,
                            QString p_strFinalScore,
                            bool p_bFinalApparatus)
{
    QString strFinalApparatus = p_bFinalApparatus ? "FinalApparatus" : "";
    qDebug() << "onSaveScore(): " << p_strGymnastFullTxt <<  ", "
                << p_strApparatus <<  ", "
                << p_strDifficultyScore <<  ", "
                << p_strFinalScore <<   ", "
                << strFinalApparatus;

    QString strErr = "";
    bool bConvDifficultyScoreOk = false;
    float fDifficultyScore = CheckDifficultyScore(p_strDifficultyScore, &bConvDifficultyScoreOk);
    if (!bConvDifficultyScoreOk)
    {
        strErr = "Nota di partenza non é tra 0 e 10";
    }

    bool bConvExecutionScoreOk = false;
    float fExecutionScore = CheckExecutionScore(p_strExecutionScore, &bConvExecutionScoreOk);
    if (!bConvExecutionScoreOk)
    {
        strErr = "Nota di esecuzione non é tra 0 e 20";
    }

    bool bConvPenaltyScoreOk = false;
    float fPenaltyScore = CheckPenaltyScore(p_strPenaltyScore, &bConvPenaltyScoreOk);
    fPenaltyScore *= -1;    // store it as negative value
    if (!bConvPenaltyScoreOk)
    {
        strErr = "Nota di esecuzione non é tra 0 e 10";
    }

    bool bConvFinalScoreOk = false;
    float fFinalScore = CheckFinalScore(p_strFinalScore, &bConvFinalScoreOk);

    if (!bConvFinalScoreOk)
    {
        if (!strErr.isEmpty())
            strErr += "\n";

        strErr += "La nota finale non é tra 0 e 20";
    }

    // save it to DB
    SendToDb(p_strGymnastFullTxt, p_strApparatus, fDifficultyScore, fExecutionScore, fPenaltyScore, fFinalScore, p_bFinalApparatus);

    // Show it to the user
    if ((!bConvDifficultyScoreOk) || (!bConvExecutionScoreOk) || (!bConvPenaltyScoreOk) || (!bConvFinalScoreOk))
    {
        MessageBox cMsgBox;
        cMsgBox.SetTitle("Warning");
        cMsgBox.SetText(strErr);
        cMsgBox.Show();
    }
}

float SaveScore::CheckDifficultyScore(QString p_strInputVal, bool* bOk)
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

float SaveScore::CheckExecutionScore(QString p_strInputVal, bool* bOk)
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

float SaveScore::CheckPenaltyScore(QString p_strInputVal, bool* bOk)
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
                         float p_fDifficultyScore,
                         float p_fExecutionScore,
                         float p_fPenaltyScore,
                         float p_fFinalScore,
                         bool p_bFinalApparatus)
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
                                             iApparatusId, p_fDifficultyScore, p_fExecutionScore,
                                             p_fPenaltyScore, p_fFinalScore, p_bFinalApparatus);
    }
    else
    {
        // insert a new one
        dbInterface::Instance()->setNewScore(iEventId, iAthleteId,
                                             iApparatusId, p_fDifficultyScore, p_fExecutionScore,
                                             p_fPenaltyScore, p_fFinalScore, p_bFinalApparatus);
    }
}
