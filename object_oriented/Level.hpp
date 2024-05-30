#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Block.hpp"
#include "Plane.hpp"

class Level
{
private:
    Block* empit;
    Block* blocked;
    Plane* plane;
    Block*** level;
protected:
    const int LEVEL_WIDTH = 32;
    const int LEVEL_HEIGTH = 8;
public:
    Level(Block* empit, Block* Blocked, Plane* Plane);
    ~Level();

    void generateNewObstaclesLine();
    void swapObstaclesToFrontLines();
    //TODO join generateNewObstaclesLine() and swapObstaclesToFrontLines()
    void updatePath();
    //TODO plane change position
    void updatePlane();
    //TODO print scream
    void returnScreen();
};

Level::Level(Block* empit, Block* blocked, Plane* plane)
{
    this->empit = empit;
    this->blocked = blocked;
    this->plane = plane;

    this->level = (Block***) std::malloc(LEVEL_WIDTH*sizeof(Block*));
    for (size_t i = 0; i < LEVEL_WIDTH; i++)
    {
        this->level[i] = (Block**) std::malloc(LEVEL_HEIGTH*sizeof(Block*));
    }
    for (size_t i = 0; i < LEVEL_WIDTH; i++)
    {
        for (size_t j = 0; j < LEVEL_HEIGTH; j++)
        {
            this->level[i][j] = empit;
        }
    }
    
};

Level::~Level()
{

};

#endif 