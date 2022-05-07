#include "zombie.h"
#include <cstdlib>
#include "map.h"
#include "ncurses.h"

Zombie::Zombie(int r, int c): Sprite('Z', r, c)
{}

Zombie::~Zombie()
{}

Zombie *Zombie::getZombie(int r, int c)
{
    return new Zombie(r, c);
}

int Zombie::action(Map &map)
{

    if (rand() % 20 == 0) {
        map.sprites[row][col] = NULL;
        mvaddch(row + 1, col + 1, map.board[row][col]->getChar());
        map.remove_from_list(this);
        delete this; // make constructor private for all things that can delete themselves
        return -1;
    }

    int n;

    if (!(rand() % 10)) {
        n = rand() % 4; // could be calling zombie.move(map) to allow for vistors
        map.validMove(*this, dirs[n][0], dirs[n][1]) && map.move(*this, dirs[n][0], dirs[n][1]);
    }

    return 0;
}
