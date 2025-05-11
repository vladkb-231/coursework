#include "basicsimulation.h"
#include <QRandomGenerator>
#include <QDebug>

BasicSimulation::BasicSimulation(QObject* parent) : QObject(parent) {
    connect(&m_timer, &QTimer::timeout, this, &BasicSimulation::onNextEvent);
}

void BasicSimulation::simulateStepByStep(Match* match, const GameRules& rules) {
    if (m_timer.isActive())
        m_timer.stop();

    m_currentMatch = match;
    m_rules = rules;
    m_team1Score = 0;
    m_team2Score = 0;

    emit scoreUpdated(m_team1Score, m_team2Score);
    emit eventOccurred(QString("Матч %1 vs %2 начался").arg(match->team1()->name()).arg(match->team2()->name()));

    m_timer.start(50); // Быстрый таймер для имитации событий
}

void BasicSimulation::onNextEvent() {
    if (!m_currentMatch) {
        m_timer.stop();
        return;
    }

    generateNextEvent();

    // Проверяем, завершился ли матч
    if ((m_team1Score >= m_rules.pointsPerSet || m_team2Score >= m_rules.pointsPerSet) &&
        qAbs(m_team1Score - m_team2Score) >= 2) {

        m_timer.stop();

        QMap<Player*, int> scores;

        const QList<Player*>& players1 = m_currentMatch->team1()->players();
        const QList<Player*>& players2 = m_currentMatch->team2()->players();

        int score1 = m_team1Score;
        int score2 = m_team2Score;

        // Равномерно распределяем очки между игроками команды 1
        for (int i = 0; i < players1.size(); ++i) {
            int val = score1 / players1.size();
            if (i == 0) val += score1 % players1.size();
            scores[players1[i]] = val;
        }

        // Равномерно распределяем очки между игроками команды 2
        for (int i = 0; i < players2.size(); ++i) {
            int val = score2 / players2.size();
            if (i == 0) val += score2 % players2.size();
            scores[players2[i]] = val;
        }

        m_currentMatch->setScore(scores);

        emit eventOccurred(QString("Матч завершён. Счёт: %1 : %2").arg(score1).arg(score2));
        emit matchFinished(m_currentMatch);

        // Сброс для следующей симуляции
        m_currentMatch = nullptr;
        m_team1Score = 0;
        m_team2Score = 0;
        return;
    }
}

void BasicSimulation::generateNextEvent() {
    bool team1Scores = QRandomGenerator::global()->bounded(2) == 0;
    if (team1Scores) {
        m_team1Score++;
        emit eventOccurred(QString("Очко команды %1").arg(m_currentMatch->team1()->name()));
    } else {
        m_team2Score++;
        emit eventOccurred(QString("Очко команды %1").arg(m_currentMatch->team2()->name()));
    }
    emit scoreUpdated(m_team1Score, m_team2Score);
}

