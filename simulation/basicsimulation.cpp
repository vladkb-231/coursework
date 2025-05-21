#include "basicsimulation.h"
#include <QRandomGenerator>
#include <QThread>

void BasicSimulation::simulate(Match* match, const GameRules& rules) {
    QRandomGenerator* rand = QRandomGenerator::global();
    Team* teams[] = {match->team1(), match->team2()};

    const int pointsToWin = rules.getPointsToWinSet();

    while(true) {
        Team* actingTeam = teams[rand->bounded(2)];
        Team* opponentTeam = (actingTeam == teams[0]) ? teams[1] : teams[0];

        MatchEvent::EventType eventType = static_cast<MatchEvent::EventType>(
            rand->bounded(4));

        bool success = calculateSuccess(actingTeam, opponentTeam, eventType, rand);

        Player* player = actingTeam->players().at(
            rand->bounded(actingTeam->players().size()));

        MatchEvent event(
            eventType,
            success,
            QDateTime::currentMSecsSinceEpoch(),
            player,
            actingTeam
            );

        match->addEvent(event);

        // Обновление счета
        if(success) {
            if(eventType == MatchEvent::Attack || eventType == MatchEvent::Serve) {
                match->updateScore(actingTeam);
            }
        } else if(eventType == MatchEvent::Attack) {
            match->updateScore(opponentTeam);
        }

        // Проверка окончания сета
        auto score = match->score();
        if(score[teams[0]] >= pointsToWin || score[teams[1]] >= pointsToWin) break;

        QThread::msleep(300); // Задержка для визуализации
    }
}

// ... calculateSuccess() остается без изменений ...

bool BasicSimulation::calculateSuccess(Team* acting, Team* opponent,
                                       MatchEvent::EventType type,
                                       QRandomGenerator* rand) {
    int baseChance = 0;
    switch(type) {
    case MatchEvent::Attack:
        baseChance = acting->attackLevel() - opponent->defenseLevel() + 50;
        break;
    case MatchEvent::Block:
        baseChance = opponent->defenseLevel() - acting->attackLevel() + 40;
        break;
    case MatchEvent::Serve:
        baseChance = acting->attackLevel() * 0.8;
        break;
    case MatchEvent::Defense:
        baseChance = acting->defenseLevel() * 1.2 - opponent->attackLevel();
        break;
    }
    return rand->bounded(100) < qBound(20, baseChance, 80);
}
