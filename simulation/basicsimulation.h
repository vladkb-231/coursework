#ifndef BASICSIMULATION_H
#define BASICSIMULATION_H

#include <QRandomGenerator>
#include "simulationstrategy.h"
#include "../model/match.h"
#include "C:\Users\drego\Documents\volleyball\model\gamerules.h"

class BasicSimulation : public SimulationStrategy {
public:
    void simulate(Match* match, const GameRules& rules) override;

private:
    bool calculateSuccess(
        Team* acting,
        Team* opponent,
        MatchEvent::EventType type,
        QRandomGenerator* rand
        );
};

#endif // BASICSIMULATION_H
