#include "savescore.h"
#include <qdebug.h>
#include "messagebox.h"

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
    MessageBox cMsgBox;
    cMsgBox.SetTitle("Warning");
    cMsgBox.SetText("Vediamo cosa fa pastriccio");
    cMsgBox.Show();

}
