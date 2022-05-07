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

Move *Zombie::action(Map &map)
{
    int n;

    if ((rand() % 15)) {
        return next;
    }

    if (!(rand() % 10)) {
        n = rand() % 4; // could be calling zombie.move(map) to allow for vistors
        map.validMove(*this, dirs[n][0], dirs[n][1]) && map.move(*this, dirs[n][0], dirs[n][1]);
    } else {
        map.moveTo(*this, map.bz_path[row][col].to.row, map.bz_path[row][col].to.col);
    }

    return next;
}
