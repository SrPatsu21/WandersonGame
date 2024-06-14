#include "./Plane.hpp"

Plane::Plane(int x, int y)
{
    this->x = x;
    this->y = y;
    //* models
    char array_plane[(Block::SIZE_X*Block::SIZE_Y)+1] = "  |  --+-D  |  ";
    char array_plane_fall[(Block::SIZE_X*Block::SIZE_Y)+1] = " * * * * * * * ";
    //*plane on game
    this->plane = new Block(array_plane);
    //*plane destroid (before lose)
    this->plane_fall = new Block(array_plane_fall);
};
Plane::Plane(int x, int y, Block* plane, Block* plane_fall)
{
    this->x = x;
    this->y = y;
    this->plane = plane;
    this->plane_fall = plane_fall;
};

void Plane::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
};
int Plane::getX()
{
    return x;
};
int Plane::getY()
{
    return y;
};
void Plane::addXPos()
{
    x++;
};
void Plane::subXPos()
{
    x--;
};
void Plane::addYPos()
{
    y++;
};
void Plane::subYPos()
{
    y--;
};
Plane::~Plane()
{
    delete plane;
    delete plane_fall; 
};
Block* Plane::getPlane()
{ 
    return plane;
};
Block* Plane::getPlaneFall()
{
    return plane_fall;
};
