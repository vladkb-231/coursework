#ifndef SIMULATIONSTRATEGY_H
#define SIMULATIONSTRATEGY_H

#include <QObject>

class Match;
class GameRules;

class SimulationStrategy : public QObject {
    Q_OBJECT
public:
    explicit SimulationStrategy(QObject* parent = nullptr)
        : QObject(parent) {}
    virtual ~SimulationStrategy() = default;
    virtual void simulate(Match* match, const GameRules& rules) = 0;
};

#endif // SIMULATIONSTRATEGY_H

