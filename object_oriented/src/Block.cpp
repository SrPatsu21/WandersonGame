#include "./Block.hpp" 

Block::Block(char* block)
{
    this->block = (char*) std::malloc((SIZE_X*SIZE_Y) * sizeof(char));
    for (size_t i = 0; i < (SIZE_X*SIZE_Y); i++)
    {
        this->block[i] = block[i];
    }
    
};
Block::~Block()
{
    delete block;
};
void Block::printLine(int line)
{
    for (size_t i = 0; i < SIZE_X; i++)
    {
        std::cout << this->block[(line*SIZE_Y+i)];
    }
};