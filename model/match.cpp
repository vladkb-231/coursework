#include "match.h"

Match::Match(Team* team1, Team* team2, QObject* parent)
    : QObject(parent), m_team1(team1), m_team2(team2)
{}

Team* Match::team1() const { return m_team1; }
Team* Match::team2() const { return m_team2; }

QMap<Player*, int> Match::score() const { return m_score; }
void Match::setScore(const QMap<Player*, int>& score) { m_score = score; }

