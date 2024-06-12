#include "./Block.hpp" 

Block::Block(char* block)
{
    block = (char*) std::malloc((SIZE_X*SIZE_Y)*sizeof(char));
};
Block::~Block()
{
    delete block;
};
void Block::printLine(int line)
{
    for (size_t i = 0; i < SIZE_X; i++)
    {
        std::cout << this->block[(line*SIZE_X+i)];
    }
};