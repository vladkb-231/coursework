#include <QRandomGenerator>
#include "basicsimulation.h"
#include <QThread>

BasicSimulation::BasicSimulation(QObject* parent)
    : SimulationStrategy(parent),
    m_currentMatch(nullptr),
    m_team1Score(0),
    m_team2Score(0)
{
    connect(&m_timer, &QTimer::timeout, this, &BasicSimulation::generateNextEvent);
}

void BasicSimulation::simulate(Match* match, const GameRules& rules) {
    if (m_timer.isActive()) m_timer.stop();

    m_currentMatch = match;
    m_rules = rules;
    m_team1Score = 0;
    m_team2Score = 0;

    emit eventOccurred("Матч начался: " + match->team1()->name() + " vs " + match->team2()->name());
    m_timer.start(500);
}

void BasicSimulation::generateNextEvent() {
    if (!m_currentMatch) return;

    Team* team1 = m_currentMatch->team1();
    Team* team2 = m_currentMatch->team2();
    QRandomGenerator* rand = QRandomGenerator::global();

    bool team1Acts = rand->bounded(2) == 0;
    Team* actingTeam = team1Acts ? team1 : team2;
    Team* opponentTeam = team1Acts ? team2 : team1;

    Match::Event::Type eventType = static_cast<Match::Event::Type>(rand->bounded(4));
    bool success = calculateSuccess(actingTeam, opponentTeam, eventType, rand);

    Player* player = actingTeam->players().at(rand->bounded(actingTeam->players().size()));

    Match::Event event(
        eventType,
        success,
        QDateTime::currentMSecsSinceEpoch(),
        player,
        actingTeam
        );
    m_currentMatch->addEvent(event);

    if (success) {
        if (eventType == Match::Event::Attack || eventType == Match::Event::Serve) {
            (team1Acts ? m_team1Score : m_team2Score)++;
        }
    } else if (eventType == Match::Event::Attack) {
        // Очко получает противоположная команда
        (team1Acts ? m_team2Score : m_team1Score)++;
    }

    emit eventOccurred(QString("[%1] %2: %3 (%4)")
                           .arg(QDateTime::fromMSecsSinceEpoch(event.timestamp()).toString("mm:ss"))
                           .arg(actingTeam->name())
                           .arg(Match::Event::typeToString(eventType))
                           .arg(success ? "Успех" : "Провал"));

    emit scoreUpdated(m_team1Score, m_team2Score);

    if ((m_team1Score >= m_rules.getPointsToWinSet() ||
         m_team2Score >= m_rules.getPointsToWinSet()) &&
        qAbs(m_team1Score - m_team2Score) >= 2)
    {
        m_timer.stop();
        if (m_currentMatch) {
            emit matchFinished(m_currentMatch);
            m_currentMatch = nullptr;
        }
    }
}

bool BasicSimulation::calculateSuccess(Team* acting, Team* opponent,
                                       Match::Event::Type type,
                                       QRandomGenerator* rand)
{
    int baseChance = 0;
    switch(type) {
    case Match::Event::Attack: baseChance = acting->attackLevel() - opponent->defenseLevel() + 50; break;
    case Match::Event::Block: baseChance = opponent->defenseLevel() - acting->attackLevel() + 40; break;
    case Match::Event::Serve: baseChance = static_cast<int>(acting->attackLevel() * 0.8); break;
    case Match::Event::Defense: baseChance = static_cast<int>(acting->defenseLevel() * 1.2 - opponent->attackLevel()); break;
    }
    return rand->bounded(100) < qBound(20, baseChance, 80);
}



