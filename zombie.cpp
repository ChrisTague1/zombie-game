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

    if (!(rand() % 7)) {
        n = rand() % 4; // could be calling zombie.move(map) to allow for vistors
        map.validMove(*this, dirs[n][0], dirs[n][1]) && map.move(*this, dirs[n][0], dirs[n][1]);
    }

    return next;
}
