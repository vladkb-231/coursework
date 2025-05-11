#ifndef GAMERULES_H
#define GAMERULES_H

struct GameRules {
    int setsToWin;
    int pointsPerSet;
    int maxPoints;

    GameRules(int sets = 3, int points = 25, int maxP = 30)
        : setsToWin(sets), pointsPerSet(points), maxPoints(maxP)
    {}
};

#endif // GAMERULES_H
