#ifndef GAMERULES_H
#define GAMERULES_H

class GameRules {
public:
    explicit GameRules(
        int setsToWin = 3,
        int maxSubstitutions = 6,
        int pointsToWinSet = 25
        );

    int getSetsToWin() const;
    int getMaxSubstitutions() const;
    int getPointsToWinSet() const;

private:
    int m_setsToWin;
    int m_maxSubstitutions;
    int m_pointsToWinSet;
};

#endif // GAMERULES_H
