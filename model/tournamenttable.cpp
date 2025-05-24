#include "tournamenttable.h"
#include "match.h"

TournamentTable::TournamentTable(QObject* parent)
    : QObject(parent) {}  // Реализация конструктора

void TournamentTable::addWin(Team* team) {
    m_wins[team]++;
    m_points[team] += 3;
}

void TournamentTable::addLoss(Team* team) {
    m_losses[team]++;
}

void TournamentTable::updateStats(Match* match) {
    QMap<Team*, int> scores = match->score();
    Team* team1 = match->team1();
    Team* team2 = match->team2();

    int score1 = scores.value(team1, 0);
    int score2 = scores.value(team2, 0);

    if (score1 > score2) {
        addWin(team1);
        addLoss(team2);
    } else if (score2 > score1) {
        addWin(team2);
        addLoss(team1);
    } else {
        // Если ничья (по правилам)
        m_points[team1] += 1;
        m_points[team2] += 1;
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
