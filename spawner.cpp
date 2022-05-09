#include "spawner.h"
#include "map.h"
#include "zombie.h"
#include <cstdlib>
#include <climits>
#include <cmath>

Spawner::Spawner(int delay, int guarantee, int possible): delay(delay), guarantee(guarantee), possible(possible)
{}

Spawner::~Spawner()
{}

Move *Spawner::action(Map &map)
{
    if(aboveZero()) {
        decrement();
        return next;
    }

    int r, c, i = guarantee + rand() % possible;

    while (i-- > 0) {
        do {
            r = rand() % height;
            c = rand() % width;
        } while (map.board[r][c]->getCost() == INT_MAX || map.sprites[r][c] || sqrt(pow(map.pc->row - r, 2.0) + pow(map.pc->col - c, 2.0)) < 5.0);

        map.sprites[r][c] = Zombie::getZombie(r, c);
        map.add_to_list(map.sprites[r][c]);
    }

    increment(delay);

    return next;
}
