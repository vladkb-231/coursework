#include "tournamenttable.h"
#include "match.h"

TournamentTable::TournamentTable(QObject* parent)
    : QObject(parent) {}

void TournamentTable::initializeTeams(const QList<Team*>& teams) {
    for (Team* team : teams) {
        if (!m_points.contains(team)) {
            m_points[team] = 0;
            m_wins[team] = 0;
            m_losses[team] = 0;
        }
    }
}

void TournamentTable::addWin(Team* team) {
    m_wins[team]++;
    m_points[team] += 3;
}

void TournamentTable::addLoss(Team* team) {
    m_losses[team]++;
}

void TournamentTable::updateStats(Match* match) {
    Team* team1 = match->team1();
    Team* team2 = match->team2();

    // Гарантируем наличие записей
    if (!m_points.contains(team1)) initializeTeams({team1});
    if (!m_points.contains(team2)) initializeTeams({team2});

    int score1 = match->score().value(team1, 0);
    int score2 = match->score().value(team2, 0);

    if (score1 > score2) {
        addWin(team1);
        addLoss(team2);
    } else {
        addWin(team2);
        addLoss(team1);
    }
}

QMap<Team*, int> TournamentTable::points() const {
    return m_points;
}

QMap<Team*, int> TournamentTable::wins() const {
    return m_wins;
}

QMap<Team*, int> TournamentTable::losses() const {
    return m_losses;
}


