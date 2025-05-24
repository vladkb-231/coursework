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
    explicit TournamentTable(QObject* parent = nullptr); // Объявление конструктора

    void updateStats(Match* match);
    QMap<Team*, int> points() const;     // Объявлен как const
    QMap<Team*, int> wins() const;       // Объявлен как const
    QMap<Team*, int> losses() const;    // Объявлен как const

private:
    void addWin(Team* team);   // Добавлен
    void addLoss(Team* team);  // Добавлен

    QMap<Team*, int> m_points;
    QMap<Team*, int> m_wins;
    QMap<Team*, int> m_losses;
};

#endif // TOURNAMENTTABLE_H


