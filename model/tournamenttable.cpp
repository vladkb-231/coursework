#include "tournamenttable.h"
#include <QDebug>

TournamentTable::TournamentTable(QObject* parent) : QObject(parent) {}

void TournamentTable::updateStats(Match* match) {
    if (!match) return;

    auto scores = match->score();
    Team* team1 = match->team1();
    Team* team2 = match->team2();

    int score1 = 0;
    int score2 = 0;

    for (auto it = scores.constBegin(); it != scores.constEnd(); ++it) {
        Player* player = it.key();
        int playerScore = it.value();
        if (player->team() == team1) score1 += playerScore;
        else if (player->team() == team2) score2 += playerScore;
    }

    qDebug() << "Матч:" << team1->name() << score1 << "-" << team2->name() << score2;

    if (score1 > score2) {
        addWin(team1);
        addLoss(team2);
    } else if (score2 > score1) {
        addWin(team2);
        addLoss(team1);
    } else {
        m_points[team1] += 1;
        m_points[team2] += 1;
    }
}

void TournamentTable::addWin(Team* team) {
    m_wins[team]++;
    m_points[team] += 3;
}

void TournamentTable::addLoss(Team* team) {
    m_losses[team]++;
}

QMap<Team*, int> TournamentTable::points() const { return m_points; }
QMap<Team*, int> TournamentTable::wins() const { return m_wins; }
QMap<Team*, int> TournamentTable::losses() const { return m_losses; }

