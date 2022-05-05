#include "character.h"

char Character::getChar()
{
    return c;
};

void Character::updatePos(int dy, int dx)
{
    row += dy;
    col += dx;
}

Character::Character(char ch, int r, int c): c(ch), row(r), col(c)
{}

Character::~Character()
{}
