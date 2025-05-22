#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include <QString>
#include <QList>

// Forward declaration класса Player
class Player;

class Team : public QObject {
    Q_OBJECT
public:
    explicit Team(const QString& name, QObject* parent = nullptr);

    QString name() const;
    QList<Player*> players() const;

    void addPlayer(Player* player);

private:
    QString m_name;
    QList<Player*> m_players;
};

#endif // TEAM_H

