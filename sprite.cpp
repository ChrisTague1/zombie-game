#include "sprite.h"

char Sprite::getChar()
{
    return c;
};

void Sprite::updatePos(int dy, int dx)
{
    row += dy;
    col += dx;
}

Sprite::Sprite(char ch, int r, int c, int health): c(ch), row(r), col(c), health(health)
{}
