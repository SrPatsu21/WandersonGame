#ifndef PLANE_HPP
#define PLANE_HPP

#include "Block.hpp"

class Plane
{
private:
    int x;
    int y;
protected:
    Block* plane;
    Block* plane_fall;
    void setPos(int x, int y);
public:
    //* Plane has a default Block, but you can define it
    Plane(int x, int y);
    Plane(int x, int y, Block* plane, Block* plane_fall);
    ~Plane();
    int getX();
    int getY();
    //*change x to x+1
    void addXPos();
    //*change x to x-1
    void subXPos();
    //*change y to y+1
    void addYPos();
    //*change y to y-1
    void subYPos();
    //*print plane format
    virtual Block* getPlane();
    //*print fall plane format
    virtual Block* getPlaneFall();
};
#endif