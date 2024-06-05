#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <iostream>

class Block
{
private:
    char* block;
public:
    static const int SIZE_X = 4;
    static const int SIZE_Y = 3;
    Block(char* block);
    ~Block();
    //*SIZE_Y is the amount of lines that need to be printed for a full block
    virtual void printLine(int line);
};

#endif