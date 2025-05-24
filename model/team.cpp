#include "team.h"

Team::Team(const QString& name, QObject* parent)
    : QObject(parent),
    m_name(name),
    m_attackLevel(0),
    m_defenseLevel(0) {}

QString Team::name() const {
    return m_name;
}

QList<Player*> Team::players() const {
    return m_players;
}

void Team::addPlayer(Player* player) {
    if (!m_players.contains(player)) {
        m_players.append(player);
        calculateStats();
    }
}

void Team::calculateStats() {
    int totalAttack = 0, totalDefense = 0;
    for (const auto& player : m_players) {
        totalAttack += player->attack();
        totalDefense += player->speed();
    }
    m_attackLevel = m_players.isEmpty() ? 0 : totalAttack / m_players.size();
    m_defenseLevel = m_players.isEmpty() ? 0 : totalDefense / m_players.size();
    emit statsChanged();
}

int Team::attackLevel() const {
    return m_attackLevel;
}

int Team::defenseLevel() const {
    return m_defenseLevel;
}

