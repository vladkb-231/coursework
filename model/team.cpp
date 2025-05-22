#include "team.h"
#include "player.h"

Team::Team(const QString& name, QObject* parent)
    : QObject(parent), m_name(name)
{}

QString Team::name() const {
    return m_name;
}

QList<Player*> Team::players() const {
    return m_players;
}

void Team::addPlayer(Player* player) {
    if (!m_players.contains(player)) {
        m_players.append(player);
    }
}
