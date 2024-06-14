#include "./Base.hpp"
#include "./Block.hpp"
#include "./Level.hpp"
#include "./Plane.hpp"
#include <iostream>
#include <thread>

auto gameRun(Level* level)
{
    level->run();
}
auto playerControl(Level* level)
{
    level->playerControl();
}

int main()
{
    //* clear screen to avoid thrash
    system(CLEAR);
    //* set array
    char array_empit[(Block::SIZE_X*Block::SIZE_Y)];
    char array_blocked[(Block::SIZE_X*Block::SIZE_Y)];

    for (size_t i = 0; i < (Block::SIZE_X*Block::SIZE_Y); i++)
    {
        array_empit[i] = ((char)CHAR_FREE);
        array_blocked[i] = ((char)CHAR_BLOCK);
    }
    //* define blocks
    Plane* plane = new Plane(0, 0);
    Block* empit_block = new Block(array_empit);
    Block* blocked_block = new Block(array_blocked);
    //* create level
    Level* level = new Level(5, plane, empit_block, blocked_block);

    //* create thread
    std::thread t_level_updata(gameRun, level);
    std::thread t_player_control(playerControl, level);

    //* run thread
    t_level_updata.join();
    t_player_control.join();

    //* delete all
    delete level;
    delete empit_block;
    delete blocked_block;
    std::cout << std::endl;
    return 0;
}
