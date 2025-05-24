#ifndef BASICSIMULATION_H
#define BASICSIMULATION_H

#include <QObject>
#include <QTimer>
#include "simulationstrategy.h"
#include "C:\Users\drego\Documents\volleyball\model\team.h"
#include "C:\Users\drego\Documents\volleyball\model\match.h"
#include "C:\Users\drego\Documents\volleyball\model\gamerules.h"
#include "C:\Users\drego\Documents\volleyball\model\tournament.h"
#include <QRandomGenerator>

class BasicSimulation : public SimulationStrategy {
    Q_OBJECT
public:
    explicit BasicSimulation(QObject* parent = nullptr);
    void simulate(Match* match, const GameRules& rules) override;

signals:
    void eventOccurred(const QString& eventDescription);
    void scoreUpdated(int team1Score, int team2Score);
    void matchFinished(Match* match);

private:
    void generateNextEvent();
    bool calculateSuccess(Team* acting, Team* opponent,
                          Match::Event::Type type,
                          QRandomGenerator* rand);

    QTimer m_timer;
    Match* m_currentMatch;
    GameRules m_rules;
    int m_team1Score;
    int m_team2Score;
};

#endif // BASICSIMULATION_H
