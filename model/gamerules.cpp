#include "gamerules.h"

GameRules::GameRules(int setsToWin, int maxSubstitutions, int pointsToWinSet)
    : m_setsToWin(setsToWin),
    m_maxSubstitutions(maxSubstitutions),
    m_pointsToWinSet(pointsToWinSet) {}

int GameRules::getSetsToWin() const { return m_setsToWin; }
int GameRules::getMaxSubstitutions() const { return m_maxSubstitutions; }
int GameRules::getPointsToWinSet() const { return m_pointsToWinSet; }
