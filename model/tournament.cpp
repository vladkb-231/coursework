#include "tournament.h"
#include "tournamenttable.h"

Tournament::Tournament(QObject* parent)
    : QObject(parent), m_table(new TournamentTable(this))
{}

Tournament::Tournament(const QString& name, QObject* parent)
    : QObject(parent), m_name(name), m_table(new TournamentTable(this))
{}

void Tournament::addTeam(Team* team) {
    if (!m_teams.contains(team)) {
        m_teams.append(team);
        m_table->initializeTeams(m_teams); // Важная строка!
    }
}

void Tournament::generateSchedule() {
    m_schedule.clear();
    for (int i = 0; i < m_teams.size(); ++i) {
        for (int j = i + 1; j < m_teams.size(); ++j) {
            Match* match = new Match(m_teams[i], m_teams[j], this);
            m_schedule.append(match);
        }
    }
    emit scheduleGenerated();
}

void Tournament::updateTournament(Match* match) {
    m_table->updateStats(match);
    emit tournamentUpdated();
}

QString Tournament::name() const { return m_name; }
QList<Team*> Tournament::teams() const { return m_teams; }
QList<Match*> Tournament::schedule() const { return m_schedule; }
TournamentTable* Tournament::table() const { return m_table; }
