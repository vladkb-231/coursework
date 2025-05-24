#ifndef GAMERULES_H
#define GAMERULES_H

class GameRules {
public:
    explicit GameRules(int setsToWin = 3,
                       int maxSubstitutions = 6,
                       int pointsToWinSet = 25); // 25 очков за сет

    // Исправленные названия методов
    int getSetsToWin() const;
    int getMaxSubstitutions() const;
    int getPointsToWinSet() const;  // Бывший pointsPerSet

private:
    int m_setsToWin;
    int m_maxSubstitutions;
    int m_pointsToWinSet; // Переименовано из pointsPerSet
};

#endif // GAMERULES_H
