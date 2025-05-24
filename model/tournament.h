#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <QObject>
#include <QList>
#include "team.h"
#include "match.h"
#include "tournamenttable.h"

class Tournament : public QObject {
    Q_OBJECT
public:
    explicit Tournament(QObject* parent = nullptr);
    Tournament(const QString& name, QObject* parent = nullptr);

    void addTeam(Team* team);
    void generateSchedule();
    void updateTournament(Match* match);

    QString name() const;
    QList<Team*> teams() const;
    QList<Match*> schedule() const;
    TournamentTable* table() const;

signals:
    void scheduleGenerated();
    void tournamentUpdated();

private:
    QString m_name;
    QList<Team*> m_teams;
    QList<Match*> m_schedule;
    TournamentTable* m_table;
};

#endif // TOURNAMENT_H

