#ifndef BASICSIMULATION_H
#define BASICSIMULATION_H

#include <QObject>
#include <QTimer>
#include "C:\Users\drego\Documents\volleyball\model\match.h"
#include "C:\Users\drego\Documents\volleyball\model\gamerules.h"
#include "C:\Users\drego\Documents\volleyball\model\matchevent.h"

class BasicSimulation : public QObject {
    Q_OBJECT
public:
    explicit BasicSimulation(QObject* parent = nullptr);

    void simulateStepByStep(Match* match, const GameRules& rules);

signals:
    void eventOccurred(const QString& eventDescription);
    void scoreUpdated(int team1Score, int team2Score);
    void matchFinished(Match* match);

private slots:
    void onNextEvent();

private:
    Match* m_currentMatch = nullptr;
    GameRules m_rules;
    int m_team1Score = 0;
    int m_team2Score = 0;
    QTimer m_timer;

    void generateNextEvent();
};


#endif // BASICSIMULATION_H
