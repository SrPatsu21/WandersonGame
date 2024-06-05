#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Block.hpp"
#include "Plane.hpp"
#include <iostream>
#include <list>
#include "Base.hpp"

class Level
{
private:
    Block* empit;
    Block* blocked;
    Plane* plane;
    //*the last line is the line that will be generated
    //![y] [x]
    Block*** level;
protected:
    const int LEVEL_WIDTH = 32;
    const int LEVEL_HEIGTH = 8;
public:
    Level(Block* empit, Block* Blocked, Plane* Plane);
    ~Level();
    //*make all the full blocks walk back
    //TODO end game feature
    void swapObstaclesToFrontLines();
    //* create new full blocks on back line
    //TODO random generation
    void generateNewObstaclesLine();
    //TODO join generateNewObstaclesLine() and swapObstaclesToFrontLines()
    void updatePath();
    //TODO plane change position
    void updatePlane();
    //TODO print scream
    void returnScreen();
};

Level::Level(Block* empit, Block* blocked, Plane* plane)
{
    //*set lvl parameters
    this->empit = empit;
    this->blocked = blocked;
    this->plane = plane;
    //*alloc the Level
    this->level = (Block***) std::malloc(LEVEL_HEIGTH*sizeof(Block*));
    for (size_t i = 0; i < LEVEL_HEIGTH; i++)
    {
        this->level[i] = (Block**) std::malloc((LEVEL_WIDTH+1)*sizeof(Block*));
    }
    //*set lvl empit
    for (size_t i = 0; i < LEVEL_HEIGTH; i++)
    {
        for (size_t j = 0; j < (LEVEL_WIDTH+1); j++)
        {
            this->level[i][j] = empit;
        }
    }
    
};

Level::~Level()
{
    for (size_t i = 0; i < LEVEL_HEIGTH; i++)
    {
        for (size_t j = 0; j < (LEVEL_WIDTH+1); j++)
        {
            delete this->level[i][j];
        }
    }
    for (size_t i = 0; i < LEVEL_HEIGTH; i++)
    {
        delete this->level[i];
    }
    delete this->level;
};
void Level::swapObstaclesToFrontLines()
{
    //* if plane is no colliding
    if (this->level[this->plane->getY()][this->plane->getX()+1] != blocked)
    {
        for (size_t i = 0; i < LEVEL_HEIGTH; i++)
        {
            for (size_t j = 0; j < LEVEL_WIDTH; j++)
            {
                //*plane cant be moved back
                if (plane->getPlane() != this->level[i][j])
                {
                    //*plane cant be duplicated
                    if (plane->getPlane() != this->level[i][(j+1)])
                    {
                        this->level[i][j] = this->level[i][(j+1)];
                    }else
                    {
                        this->level[i][j] = empit;
                    }
                }
            }
        }
    }else
    {
        //! end game, lose
        for (size_t i = 0; i < LEVEL_HEIGTH; i++)
        {
            for (size_t j = 0; j < LEVEL_WIDTH; j++)
            {
                //*plane cant be moved back
                if (plane->getPlane() != this->level[i][j])
                {
                    //*plane cant be duplicated
                    if (plane->getPlane() != this->level[i][(j+1)])
                    {
                        this->level[i][j] = this->level[i][(j+1)];
                    }else
                    {
                        this->level[i][j] = empit;
                    }
                }else
                {
                    this->level[i][j] = plane->getPlaneFall();
                }
            }
        }
    }
};
void Level::generateNewObstaclesLine()
{
    for (size_t i = 0; i < LEVEL_HEIGTH; i++)
    {
        this->level[i][(LEVEL_WIDTH+1)] = blocked;
    }
};

void Level::returnScreen()
{
    //*print bord
    //TODO function to print the bord
    for (size_t i = 0; i < LEVEL_WIDTH; i++)
    {
        std::cout <<CHAR_BORD;
    }
    //*print the path
    for (size_t i = 0; i < LEVEL_HEIGTH; i++)
    {
        for (size_t j = 0; j < Block::SIZE_Y; j++)
        {
            std::cout <<CHAR_WALL;
            for (size_t k = 0; k < LEVEL_WIDTH; k++)
            {
                this->level[i][k]->printLine(j);
            }
        }
        
    }
    //*print bord
    //TODO function to print the bord
    for (size_t i = 0; i < LEVEL_WIDTH; i++)
    {
        std::cout <<CHAR_BORD;
    }
};

#endif 