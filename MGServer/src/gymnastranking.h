#ifndef GYMNASTRANKING_H
#define GYMNASTRANKING_H

#include <QList>
#include "athletedata.h"
#include "singlemwdata.h"
#include "apparatuslist.h"

class GymnastRanking
{
public:
    GymnastRanking();

    QList<AthleteData>* getAllroundMenList();
    QList<AthleteData>* getAllroundWomenList();

    QList<SingleMWData>* getSingleMenList();
    QList<SingleMWData>* getSingleWomenList();

    void updateAllroundScores();
    void updateSingleScores(ApparatusList::EApparatusMen p_eAppMen);
    void updateSingleScores(ApparatusList::EApparatusWomen p_eAppWomen);

public slots:
    void createLists();

private:

    void retrieveGymnastList(const QString& p_strGender);
    void updateAllroundMenScores();
    void updateAllroundWomenScores();
    void updateSingleScores(int p_iApparatusId, QList<SingleMWData>* p_pList);

    void setApparatus(ApparatusList::EApparatusMen p_eAppMen);
    void setApparatus(ApparatusList::EApparatusWomen p_eAppWomen);


    /** Alround Men's ranking */
    QList<AthleteData> m_MenList;

    /** Allround Women's Ranking */
    QList<AthleteData> m_WomenList;

    /** Men Single apparatus ranking list.
     *  Used for city trophy */
    QList<SingleMWData> m_singleMApparatusList;

    /** Women Single apparatus ranking list.
     *  Used for city trophy */
    QList<SingleMWData> m_singleWApparatusList;

};

#endif // GYMNASTRANKING_H
