#include "sprite.h"

void Sprite::updatePos(int dy, int dx)
{
    row += dy;
    col += dx;
}

Sprite::Sprite(char ch, int r, int c, int health): Cell(ch), row(r), col(c), health(health)
{}
