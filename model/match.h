#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QMutex>
#include <QDateTime>
#include "team.h"
#include "gamerules.h"

class MatchEvent {
public:
    enum EventType { Attack, Block, Serve, Defense };

    MatchEvent(EventType type, bool success, qint64 timestamp,
               Player* player, Team* team);

    EventType type() const;
    bool isSuccessful() const;
    qint64 timestamp() const;
    Player* player() const;
    Team* team() const;

private:
    EventType m_type;
    bool m_success;
    qint64 m_timestamp;
    Player* m_player;
    Team* m_team;
};

class Match : public QObject {
    Q_OBJECT
public:
    Match(Team* team1, Team* team2, QObject* parent = nullptr);
    ~Match();

    Team* team1() const;
    Team* team2() const;
    QMap<Team*, int> score() const;
    QList<const MatchEvent*> events() const;

    void addEvent(const MatchEvent& event);
    void updateScore(Team* scoringTeam, int points = 1);

signals:
    void eventAdded(const MatchEvent& event);
    void scoreChanged(int team1Score, int team2Score);

private:
    mutable QMutex m_mutex;
    Team* m_team1;
    Team* m_team2;
    QList<MatchEvent*> m_events;
    QMap<Team*, int> m_score;
};

#endif // MATCH_H
