#include "./Base.hpp"
#include "./Block.hpp"
#include "./Level.hpp"
#include "./Plane.hpp"
#include <iostream>

int main()
{
    // Plane* plane = new Plane(0, 0);
    // plane->getPlane()->printLine(0);
    // std::cout << std::endl;
    // plane->getPlane()->printLine(1);
    // std::cout << std::endl;
    // plane->getPlane()->printLine(2);

    char array_empit[(Block::SIZE_X*Block::SIZE_Y)];
    char array_blocked[(Block::SIZE_X*Block::SIZE_Y)];
    for (size_t i = 0; i < (Block::SIZE_X*Block::SIZE_Y); i++)
    {
        array_empit[i] = ((char)CHAR_FREE);
        array_blocked[i] = ((char)CHAR_BLOCK);
    }
    
    Level* level = new Level(new Plane(0, 0), new Block(array_empit), new Block(array_blocked));
    level->returnScreen();
    
    delete level;
    std::cout << std::endl;
    return 0;
}
