#include "match.h"
#include "player.h"
#include "team.h"

Match::Match(Team* team1, Team* team2, QObject* parent)
    : QObject(parent), m_team1(team1), m_team2(team2)
{
    m_score[team1] = 0;
    m_score[team2] = 0;
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
    m_playerEventCounts[event.player()]++;
    emit eventAdded(event);
}

void Match::updateScore(Team* team, int score) {
    if (team == m_team1 || team == m_team2) {
        m_score[team] = score;
    }
}

bool Match::isFinished() const {
    int score1 = m_score.value(m_team1, 0);
    int score2 = m_score.value(m_team2, 0);
    const bool isTieBreak = (score1 >= 24 && score2 >= 24);
    const int pointsToWin = isTieBreak ? 26 : 25;
    return (score1 >= pointsToWin || score2 >= pointsToWin) &&
           qAbs(score1 - score2) >= 2;
}

Player* Match::getBestPlayer() const {
    Player* best = nullptr;
    int max = 0;
    for (auto it = m_playerEventCounts.constBegin(); it != m_playerEventCounts.constEnd(); ++it) {
        if (it.value() > max) {
            max = it.value();
            best = it.key();
        }
    }
    return best;
}

int Match::getBestPlayerCount() const {
    Player* best = getBestPlayer();
    return best ? m_playerEventCounts.value(best) : 0;
}

Team* Match::team1() const { return m_team1; }
Team* Match::team2() const { return m_team2; }
QMap<Team*, int> Match::score() const {
    return {{m_team1, m_score[m_team1]}, {m_team2, m_score[m_team2]}};
}

Match::Event::Type Match::Event::type() const { return m_type; }
bool Match::Event::isSuccessful() const { return m_success; }
qint64 Match::Event::timestamp() const { return m_timestamp; }
Player* Match::Event::player() const { return m_player; }
Team* Match::Event::team() const { return m_team; }

