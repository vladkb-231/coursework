#include "match.h"
#include "player.h"
#include "team.h"

Match::Match(Team* team1, Team* team2, QObject* parent)
    : QObject(parent), m_team1(team1), m_team2(team2)
{
    m_score[team1] = 0;
    m_score[team2] = 0;
    // Добавлено обнуление при создании матча
}

Match::Event::Event(Type type, bool success, qint64 timestamp,
                    Player* player, Team* team)
    : m_type(type),
    m_success(success),
    m_timestamp(timestamp),
    m_player(player),
    m_team(team) {}

void Match::addEvent(const Event& event) {
    m_events.append(new Event(event));
    emit eventAdded(event);
}

void Match::updateScore(Team* team, int score) { // Новая реализация
    if (team == m_team1 || team == m_team2) {
        m_score[team] = score;
    }
}

Team* Match::team1() const { return m_team1; }
Team* Match::team2() const { return m_team2; }
QMap<Team*, int> Match::score() const {
    return {{m_team1, m_score[m_team1]}, {m_team2, m_score[m_team2]}};
}

// Реализация методов Event
Match::Event::Type Match::Event::type() const { return m_type; }
bool Match::Event::isSuccessful() const { return m_success; }
qint64 Match::Event::timestamp() const { return m_timestamp; }
Player* Match::Event::player() const { return m_player; }
Team* Match::Event::team() const { return m_team; }
