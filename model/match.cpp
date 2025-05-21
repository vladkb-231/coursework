#include "match.h"

MatchEvent::MatchEvent(EventType type, bool success, qint64 timestamp,
                       Player* player, Team* team)
    : m_type(type), m_success(success), m_timestamp(timestamp),
    m_player(player), m_team(team)
{
    Q_ASSERT_X(player, "MatchEvent", "Player is null");
    Q_ASSERT_X(team, "MatchEvent", "Team is null");
}

MatchEvent::EventType MatchEvent::type() const { return m_type; }
bool MatchEvent::isSuccessful() const { return m_success; }
qint64 MatchEvent::timestamp() const { return m_timestamp; }
Player* MatchEvent::player() const { return m_player; }
Team* MatchEvent::team() const { return m_team; }

Match::Match(Team* team1, Team* team2, QObject* parent)
    : QObject(parent), m_team1(team1), m_team2(team2)
{
    m_score[m_team1] = 0;
    m_score[m_team2] = 0;
}

Match::~Match() {
    QMutexLocker locker(&m_mutex);
    qDeleteAll(m_events);
}

Team* Match::team1() const { return m_team1; }
Team* Match::team2() const { return m_team2; }

QMap<Team*, int> Match::score() const {
    QMutexLocker locker(&m_mutex);
    return m_score;
}

QList<const MatchEvent*> Match::events() const {
    QMutexLocker locker(&m_mutex);
    QList<const MatchEvent*> result;
    for(auto e : m_events) result << e;
    return result;
}

void Match::addEvent(const MatchEvent& event) {
    QMutexLocker locker(&m_mutex);
    MatchEvent* newEvent = new MatchEvent(event);
    m_events.append(newEvent);
    emit eventAdded(*newEvent);
}

void Match::updateScore(Team* scoringTeam, int points) {
    QMutexLocker locker(&m_mutex);
    if(m_score.contains(scoringTeam)) {
        m_score[scoringTeam] += points;
        emit scoreChanged(m_score[m_team1], m_score[m_team2]);
    }
}
