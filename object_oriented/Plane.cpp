#include "./Plane.hpp"

Plane::Plane(int x = 0, int y = 0)
{
    this->x = x;
    this->y = y;
    this->plane = new Block("|\\    \\\n  ====|===>\n|/    /"); //representação do avião no jogo
    this->plane_fall = new Block("|\\    \\\n  ====|===>\n|/    /"); // quando ele estiver caindo
};
Plane::Plane(int x = 0, int y = 0, Block* plane, Block* plane_fall)
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
