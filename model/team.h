#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include <QString>
#include <QList>
#include "C:\Users\drego\Documents\volleyball\model\player.h"

class Player;

class Team : public QObject {
    Q_OBJECT
public:
    explicit Team(const QString& name, QObject* parent = nullptr);

    QString name() const;
    QList<Player*> players() const;
    void addPlayer(Player* player);
    void calculateStats();

    int attackLevel() const;
    int defenseLevel() const;

signals:
    void statsChanged();

private:
    QString m_name;
    QList<Player*> m_players;
    int m_attackLevel;
    int m_defenseLevel;
};



#endif // TEAM_H
