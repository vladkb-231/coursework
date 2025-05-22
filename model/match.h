#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QMap>
#include "team.h"
#include "player.h"

class Match : public QObject {
    Q_OBJECT
public:
    explicit Match(Team* team1, Team* team2, QObject* parent = nullptr);

    Team* team1() const;
    Team* team2() const;

    // Очки игроков в матче
    QMap<Player*, int> score() const;
    void setScore(const QMap<Player*, int>& score);

private:
    Team* m_team1;
    Team* m_team2;
    QMap<Player*, int> m_score;
};

#endif // MATCH_H



