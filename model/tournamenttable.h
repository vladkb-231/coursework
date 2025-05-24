#ifndef TOURNAMENTTABLE_H
#define TOURNAMENTTABLE_H

#include <QObject>
#include <QMap>
#include "C:\Users\drego\Documents\volleyball\model\match.h"

class Team;
class Match;

class TournamentTable : public QObject {
    Q_OBJECT
public:
    explicit TournamentTable(QObject* parent = nullptr);

    void initializeTeams(const QList<Team*>& teams); // Добавленный метод
    void updateStats(Match* match);

    QMap<Team*, int> points() const;
    QMap<Team*, int> wins() const;
    QMap<Team*, int> losses() const;

private:
    void addWin(Team* team);
    void addLoss(Team* team);

    QMap<Team*, int> m_points;
    QMap<Team*, int> m_wins;
    QMap<Team*, int> m_losses;
};


#endif // TOURNAMENTTABLE_H
