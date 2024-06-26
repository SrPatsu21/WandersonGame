#include "./Level.hpp"
#include "Base.hpp"

Level::Level(int difficult, Plane* plane, Block* empit, Block* blocked)
{
    //*set lvl parameters
    this->empit = empit;
    this->blocked = blocked;
    this->plane = plane;
    this->score = 0;
    this->player_move = '\0';
    this->difficult = difficult;
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
                //* plane cant be moved back
                //* plane cant be overwrited
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
    //* score
    std::cout << "score:" << score << std::endl;
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

void Level::updatePlane(char key)
{
    bool isvalidmove = false;
    if ('w' == key || 'W' == key)
    {
        if (0 < plane->getY())
        {
            isvalidmove = true;
            level[(plane->getY()*LEVEL_WIDTH+plane->getX())] = empit;
            plane->subYPos();     
        }
        
    }else if('s' == key || 'S' == key)
    {
        if ((LEVEL_HEIGTH-1) > plane->getY())
        {
            isvalidmove = true;
            level[(plane->getY()*LEVEL_WIDTH+plane->getX())] = empit;
            plane->addYPos();
        }

    }else if('a' == key || 'A' == key)
    {
        if (1 < plane->getX())
        {
            isvalidmove = true;
            level[(plane->getY()*LEVEL_WIDTH+plane->getX())] = empit;
            plane->subXPos();
        }
    }else if('d' == key || 'D' == key)
    {
        if ((LEVEL_WIDTH-1) > plane->getX())
        {
            isvalidmove = true;
            level[(plane->getY()*LEVEL_WIDTH+plane->getX())] = empit;
            plane->addXPos();
        }
    }

    if (isvalidmove)
    {
        if (level[((plane->getY())*LEVEL_WIDTH+(plane->getX()))] != blocked)
        {
            level[((plane->getY())*LEVEL_WIDTH+(plane->getX()))] = plane->getPlane();
        }else
        {
            runnig = false;
            level[((plane->getY())*LEVEL_WIDTH+(plane->getX()))] = plane->getPlaneFall();
        }    
    }

    this->player_move = '\0';
};

void Level::playerControl()
{
    while (runnig)
    {
        this->player_move = ((char)getKeyChar());
    }
};

void Level::run()
{
    int count = 0;
    runnig = true;
    while(runnig)
    {
        count++;
        updatePlane(this->player_move);
        if (count == difficult)
        {
            score++;
            count = 0;
            updatePath();
        }
        returnScreen();
        usleep(SLEEP_TIME);
    }
    returnScreen();
}