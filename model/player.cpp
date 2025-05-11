#include "player.h"

Player::Player(const QString& name, int speed, int attack, int stamina, Team* team, QObject* parent)
    : QObject(parent), m_name(name), m_speed(speed), m_attack(attack), m_stamina(stamina), m_team(team)
{}

QString Player::name() const { return m_name; }
int Player::speed() const { return m_speed; }
int Player::attack() const { return m_attack; }
int Player::stamina() const { return m_stamina; }
Team* Player::team() const { return m_team; }
void Player::setTeam(Team* team) { m_team = team; }
