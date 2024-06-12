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
    bool runnig;

    //TODO random generation
    void generateNewObstaclesLine();

    //*make all the full blocks walk back
    void swapObstaclesToFrontLines();
public:
    Level(Plane* plane, Block* empit, Block* blocked);
    Level(Plane* plane, char empit, char blocked);
    ~Level();

    //* print screen
    void returnScreen();
    //* make path walk the game run
    void updatePath();

    //*print bord
    void printBord();
    //TODO plane change position, player
    void updatePlane();

};

Level::Level(Plane* plane, Block* empit, Block* blocked)
{
    //*set lvl parameters
    this->empit = empit;
    this->blocked = blocked;
    this->plane = plane;
    //* centralize
    this->plane->setPos(2, (LEVEL_HEIGTH/2));

    //*alloc the Level
    this->level = (Block***) std::malloc(LEVEL_HEIGTH*sizeof(Block**));
    for (size_t i = 0; i < LEVEL_HEIGTH; i++)
    {
        this->level[i] = (Block**) std::malloc((LEVEL_WIDTH+1)*sizeof(Block*));
    }
    //*set lvl empit
    // for (size_t i = 0; i < LEVEL_HEIGTH; i++)
    // {
    //     for (size_t j = 0; j < (LEVEL_WIDTH+1); j++)
    //     {
    //         this->level[i][j] = empit;
    //     }
    // }
    // updatePath();
};

Level::Level(Plane* plane, char empit, char blocked)
{
    char array_empit[(Block::SIZE_X*Block::SIZE_Y)];
    char array_blocked[(Block::SIZE_X*Block::SIZE_Y)];
    for (size_t i = 0; i < (Block::SIZE_X*Block::SIZE_Y); i++)
    {
        array_empit[i] = CHAR_FREE;
        array_blocked[i] = CHAR_BLOCK;
    }
    
    Level(plane, new Block(array_empit), new Block(array_blocked));
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
        runnig = false;
    }
};

void Level::generateNewObstaclesLine()
{
    for (size_t i = 0; i < LEVEL_HEIGTH; i++)
    {
        this->level[i][(LEVEL_WIDTH+1)] = blocked;
    }
};

void Level::printBord()
{
    char c = CHAR_BORD;
    for (size_t i = 0; i < (LEVEL_WIDTH*Block::SIZE_X); i++)
    {
        std::cout << c;
    }
    std::cout << std::endl;
}

void Level::returnScreen()
{
    printBord();
    //*print the path
    for (size_t i = 0; i < LEVEL_HEIGTH; i++)
    {
        for (size_t j = 0; j < Block::SIZE_Y; j++)
        {
            std::cout << CHAR_WALL;
            for (size_t k = 0; k < LEVEL_WIDTH; k++)
            {
                this->level[i][k]->printLine(j);
            }
        }
        
    }
    printBord();

};

void Level::updatePath()
{
    generateNewObstaclesLine();
    swapObstaclesToFrontLines();
};
#endif 