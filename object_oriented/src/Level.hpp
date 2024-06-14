#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Block.hpp"
#include "Plane.hpp"
#include <iostream>
#include <list>
#include <time.h>
#include "Base.hpp"

class Level
{
private:
    Block* empit;
    Block* blocked;
    Plane* plane;
    //*the last line is the line that will be generated
    //![y] [x]
    Block** level;
protected:
    const int LEVEL_WIDTH = 28 + 1;
    const int LEVEL_HEIGTH = 8;
    const int LEVEL_WH = LEVEL_WIDTH * LEVEL_HEIGTH;
    int difficult;
    int score;
    bool runnig;
    char player_move;

    //* rand the last colum
    void generateNewObstaclesLine();

    //*make all the full blocks walk back
    void swapObstaclesToFrontLines();
    //TODO plane change position, player
    void updatePlane(char key);
public:
    Level(int difficult, Plane* plane, Block* empit, Block* blocked);
    ~Level();

    //* print screen
    void returnScreen();
    //* make path walk the game run
    void updatePath();

    //*print bord
    void printBord();
    //* game flux
    void run();
    //* chat key
    void playerControl();
};

#endif 