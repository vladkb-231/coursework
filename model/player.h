#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>

class Team; // Forward declaration

class Player : public QObject {
    Q_OBJECT
public:
    explicit Player(const QString& name,
                    int speed,
                    int attack,
                    int stamina,
                    Team* team = nullptr,
                    QObject* parent = nullptr);

    QString name() const;
    int speed() const;
    int attack() const;
    int stamina() const;
    Team* team() const;
    void setTeam(Team* team);

private:
    QString m_name;
    int m_speed;
    int m_attack;
    int m_stamina;
    Team* m_team;
};

#endif // PLAYER_H



