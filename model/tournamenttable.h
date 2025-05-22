#ifndef TOURNAMENTTABLE_H
#define TOURNAMENTTABLE_H

#include <QObject>
#include <QMap>
#include "team.h"
#include "match.h"

class TournamentTable : public QObject {
    Q_OBJECT
public:
    explicit TournamentTable(QObject* parent = nullptr);

    // Обновляет статистику на основе результата матча
    void updateStats(Match* match);

    // Получить текущие очки, победы, поражения команд
    QMap<Team*, int> points() const;
    QMap<Team*, int> wins() const;
    QMap<Team*, int> losses() const;

private:
    QMap<Team*, int> m_points;
    QMap<Team*, int> m_wins;
    QMap<Team*, int> m_losses;

    void addWin(Team* team);
    void addLoss(Team* team);
};

#endif // TOURNAMENTTABLE_H

