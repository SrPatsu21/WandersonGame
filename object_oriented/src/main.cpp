#include "./Base.hpp"
#include "./Block.hpp"
#include "./Level.hpp"
#include "./Plane.hpp"
#include <iostream>

int main()
{
    Level* level = new Level(new Plane(0, 0), CHAR_FREE, CHAR_BLOCK);
    // level->printBord();

    delete level;
    return 0;
}
