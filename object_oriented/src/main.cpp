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

    Level* level = new Level(new Plane(0, 0), CHAR_FREE, CHAR_BLOCK);
    // level->returnScreen();

    // delete level;
    std::cout << std::endl;
    return 0;
}
