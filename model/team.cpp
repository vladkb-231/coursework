#include "team.h"

TeamBuilder Team::builder() {
    return TeamBuilder();
}

Team::Team(QObject* parent) : QObject(parent),
    m_attackLevel(0), m_defenseLevel(0) {}

Team::~Team() {
    qDeleteAll(m_players);
}

void Team::calculateStats() {
    int totalAttack = 0, totalDefense = 0;
    for(const auto& player : m_players) {
        totalAttack += player->attack();
        totalDefense += player->speed();
    }
    m_attackLevel = !m_players.isEmpty() ? totalAttack / m_players.size() : 0;
    m_defenseLevel = !m_players.isEmpty() ? totalDefense / m_players.size() : 0;
    emit statsChanged();
}

QString Team::name() const { return m_name; }
int Team::attackLevel() const { return m_attackLevel; }
int Team::defenseLevel() const { return m_defenseLevel; }
QList<Player*> Team::players() const { return m_players; }

// TeamBuilder
TeamBuilder& TeamBuilder::setName(const QString& name) {
    m_name = name;
    return *this;
}

TeamBuilder& TeamBuilder::addPlayer(Player* player) {
    m_players.append(player);
    return *this;
}

Team* TeamBuilder::build(QObject* parent) {
    Team* team = new Team(parent);
    team->m_name = m_name;
    team->m_players = m_players;
    team->calculateStats();
    return team;
}

QList<Player*> TeamBuilder::getPlayers() const {
    return m_players;
}
