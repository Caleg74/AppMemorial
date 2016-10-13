#ifndef GYMNASTRANKING_H
#define GYMNASTRANKING_H

#include <QList>
#include "athletedata.h"

class GymnastRanking
{
public:
    GymnastRanking();

    QList<AthleteData>* getMenList();

    QList<AthleteData>* getWomenList();


public slots:
    void createLists();

    void updateScores();

private:

    void retrieveGymnastList(const QString& p_strGender);
    void updateMenScores();
    void updateWomenScores();

    QList<AthleteData> m_MenList;

    QList<AthleteData> m_WomenList;
};

#endif // GYMNASTRANKING_H
