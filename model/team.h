#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include <QList>
#include "player.h"

class TeamBuilder;

class Team : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(int attackLevel READ attackLevel NOTIFY statsChanged)
    Q_PROPERTY(int defenseLevel READ defenseLevel NOTIFY statsChanged)

public:
    static TeamBuilder builder();
    ~Team();

    void calculateStats();
    QString name() const;
    int attackLevel() const;
    int defenseLevel() const;
    QList<Player*> players() const;

signals:
    void statsChanged();

private:
    explicit Team(QObject* parent = nullptr);
    friend class TeamBuilder;

    QString m_name;
    QList<Player*> m_players;
    int m_attackLevel;
    int m_defenseLevel;
};

class TeamBuilder {
public:
    TeamBuilder& setName(const QString& name);
    TeamBuilder& addPlayer(Player* player);
    Team* build(QObject* parent = nullptr);
    QList<Player*> getPlayers() const;

private:
    QString m_name;
    QList<Player*> m_players;
};

#endif // TEAM_H

