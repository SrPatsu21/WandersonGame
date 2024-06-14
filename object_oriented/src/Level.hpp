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
    int score;
    bool runnig;

    //TODO random generation
    void generateNewObstaclesLine();

    //*make all the full blocks walk back
    void swapObstaclesToFrontLines();
public:
    Level(Plane* plane, Block* empit, Block* blocked);
    ~Level();

    //* print screen
    void returnScreen();
    //* make path walk the game run
    void updatePath();

    //*print bord
    void printBord();
    //TODO plane change position, player
    void updatePlane();
    //* game control
    void run();

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
    this->level = (Block**) std::malloc(LEVEL_WH*sizeof(Block*));    

    //*set lvl empit
    for (size_t i = 0; i < LEVEL_HEIGTH; i++)
    {
        for (size_t j = 0; j < LEVEL_WIDTH; j++)
        {
            this->level[(i*LEVEL_WIDTH+j)] = empit;
        }
    }
    //* inset plane
    this->level[(plane->getY()*LEVEL_WIDTH+plane->getX())] = plane->getPlane();
    //* random seed
    srand(time(NULL));
    //* creat path
    updatePath();
};

Level::~Level()
{
    delete this->level;
};

void Level::swapObstaclesToFrontLines()
{
    //* if plane is no colliding
    if (level[plane->getY()*LEVEL_WIDTH+(plane->getX()+1)] != blocked)
    {
        for (size_t i = 0; i < LEVEL_HEIGTH; i++)
        {
            for (size_t j = 0; j < LEVEL_WIDTH; j++)
            {
                //*plane cant be moved back
                if (plane->getPlane() != this->level[(i*LEVEL_WIDTH+j)])
                {
                    //*plane cant be duplicated
                    if (plane->getPlane() != level[(i*LEVEL_WIDTH+(j+1))])
                    {
                        level[(i*LEVEL_WIDTH+j)] = level[(i*LEVEL_WIDTH+(j+1))];
                    }else
                    {
                        level[(i*LEVEL_WIDTH+j)] = empit;
                    }
                }
            }
        }
    }else
    {
        //! end game, lose
        runnig = false;
        for (size_t i = 0; i < LEVEL_HEIGTH; i++)
        {
            for (size_t j = 0; j < LEVEL_WIDTH; j++)
            {
                //*plane cant be moved back
                if (plane->getPlane() != level[(i*LEVEL_WIDTH+j)])
                {
                    //*plane cant be duplicated
                    if (plane->getPlane() != level[(i*LEVEL_WIDTH+(j+1))])
                    {
                        level[(i*LEVEL_WIDTH+j)] = level[(i*LEVEL_WIDTH+(j+1))];
                    }else
                    {
                        level[(i*LEVEL_WIDTH+j)] = empit;
                    }
                }else
                {
                    level[(i*LEVEL_WIDTH+j)] = plane->getPlaneFall();
                }
            }
        }
        runnig = false;
    }
};

void Level::generateNewObstaclesLine()
{
    int pass_col = 0;
    for (size_t i = 0; i < LEVEL_HEIGTH; i++)
    {

        int r =(rand() % 3);
        if (r != 0)
        {
            pass_col++;
            level[(i*(LEVEL_WIDTH)+LEVEL_WIDTH)] = empit;
        }else
        {
            level[(i*(LEVEL_WIDTH)+LEVEL_WIDTH)] = blocked;
        }
    }

    if (pass_col == 0)
    {
        level[((rand() % LEVEL_HEIGTH)*(LEVEL_WIDTH)+LEVEL_WIDTH)] = empit;
    }
    
    for (size_t i = 1; i < LEVEL_HEIGTH-1; i++)
    {   
        if(level[((i+1)*(LEVEL_WIDTH)+LEVEL_WIDTH)] != empit && level[((i-1)*(LEVEL_WIDTH)+LEVEL_WIDTH)] != empit && level[(i*(LEVEL_WIDTH)+LEVEL_WIDTH)] != empit)
        {
            if (rand() % 2 == 0)
            {
                level[((i+1)*(LEVEL_WIDTH)+LEVEL_WIDTH)] = empit;
            }
            else
            {
                level[((i-1)*(LEVEL_WIDTH)+LEVEL_WIDTH)] = empit;
            }
        }else if(level[(i*(LEVEL_WIDTH-1)+LEVEL_WIDTH)] != empit)
        {
             level[(i*(LEVEL_WIDTH)+LEVEL_WIDTH)] = empit;
        }
    }
    
};

void Level::printBord()
{
    char c = ((char)CHAR_BORD);
    for (size_t i = 0; i < ((LEVEL_WIDTH*Block::SIZE_X)+1); i++)
    {
        std::cout << c;
    }
    std::cout << std::endl;
}

void Level::returnScreen()
{
    //*clear
    clearScreen();
    //* bord
    printBord();
    //*print the path
    for (size_t i = 0; i < LEVEL_HEIGTH; i++)
    {
        for (size_t j = 0; j < Block::SIZE_Y; j++)
        {
            std::cout << ((char)CHAR_WALL);
            for (size_t k = 0; k < LEVEL_WIDTH; k++)
            {
                level[(i*(LEVEL_WIDTH)+k)]->printLine(j);
            }
            std::cout << std::endl;    
        }    
    }
    printBord();
};

void Level::updatePath()
{
    generateNewObstaclesLine();
    swapObstaclesToFrontLines();
};

void Level::run()
{
    int count = 0;
    runnig = true;
    while(runnig)
    {
        count++;
        score++;
        if (count == 5)
        {
            count = 0;
            updatePath();
        }
        
        returnScreen();
        usleep(SLEEP_TIME);
    }
}

#endif 