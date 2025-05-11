#ifndef SIMULATIONSTRATEGY_H
#define SIMULATIONSTRATEGY_H

class Match;
class GameRules;

class SimulationStrategy {
public:
    virtual ~SimulationStrategy() = default;
    virtual void simulate(Match* match, const GameRules& rules) = 0;
};

#endif // SIMULATIONSTRATEGY_H
