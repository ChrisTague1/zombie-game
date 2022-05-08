#include "zombie.h"
#include <cstdlib>
#include "map.h"
#include "ncurses.h"

Zombie::Zombie(int r, int c): Sprite('Z', r, c)
{
    odds_moving = 10 + rand() % 5;
    odds_follow = 60 + rand() % 30;
}

Zombie::~Zombie()
{}

Zombie *Zombie::getZombie(int r, int c)
{
    return new Zombie(r, c);
}

Move *Zombie::action(Map &map)
{
    if (rand() % 100 > odds_moving) return next;

    int n = rand() % 4;

    if (rand() % 100 > odds_follow) {
        map.validMove(*this, dirs[n][0], dirs[n][1]) && map.move(*this, dirs[n][0], dirs[n][1]);
    } else {
        map.followPath(*this, map.bz_path); // should make them follow A* for a more zombie feel
    }

    return next;
}
