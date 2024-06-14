#include "./Base.hpp"
#include "./Block.hpp"
#include "./Level.hpp"
#include "./Plane.hpp"
#include <iostream>

int main()
{

    char array_empit[(Block::SIZE_X*Block::SIZE_Y)];
    char array_blocked[(Block::SIZE_X*Block::SIZE_Y)];

    for (size_t i = 0; i < (Block::SIZE_X*Block::SIZE_Y); i++)
    {
        array_empit[i] = ((char)CHAR_FREE);
        array_blocked[i] = ((char)CHAR_BLOCK);
    }
    Plane* plane = new Plane(0, 0);
    Block* empit_block = new Block(array_empit);
    Block* blocked_block = new Block(array_blocked);

    Level* level = new Level(plane, empit_block, blocked_block);
    level->run();
    
    delete level;
    delete empit_block;
    delete blocked_block;
    std::cout << std::endl;
    return 0;
}
