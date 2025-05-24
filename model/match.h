#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QMap>
#include <QDateTime>
#include <QString>
#include <QList>

class Team;
class Player;

class Match : public QObject {
    Q_OBJECT
public:
    class Event {
    public:
        enum Type { Attack, Block, Serve, Defense };

        Event(Type type, bool success, qint64 timestamp,
              Player* player, Team* team);

        static QString typeToString(Type type) {
            switch(type) {
            case Attack: return "Атака";
            case Block:  return "Блок";
            case Serve:  return "Подача";
            case Defense:return "Защита";
            default:     return "Неизвестно";
            }
        }

        Type type() const;
        bool isSuccessful() const;
        qint64 timestamp() const;
        Player* player() const;
        Team* team() const;

    private:
        Type m_type;
        bool m_success;
        qint64 m_timestamp;
        Player* m_player;
        Team* m_team;
    };

    explicit Match(Team* team1, Team* team2, QObject* parent = nullptr);

    Team* team1() const;
    Team* team2() const;
    QMap<Team*, int> score() const;
    void addEvent(const Event& event);
    void updateScore(Team* team, int score);
    bool isFinished() const;
    Player* getBestPlayer() const;
    int getBestPlayerCount() const;

signals:
    void eventAdded(const Event& event);

private:
    Team* m_team1;
    Team* m_team2;
    QMap<Team*, int> m_score;
    QList<Event*> m_events;
    QMap<Player*, int> m_playerEventCounts;
};

#endif // MATCH_H


