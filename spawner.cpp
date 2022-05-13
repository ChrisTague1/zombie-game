#include "spawner.h"
#include "map.h"
#include "zombie.h"
#include <cstdlib>
#include <climits>
#include <cmath>

#define min(x, y) x < y ? x : y

Spawner::Spawner(unsigned int zombies, int round): round(round), toSpawn(zombies) {
    increment(10);
}

Spawner::~Spawner() {}

void Spawner::spawn(int round, int toSpawn)
{
    this->round = round;
    this->toSpawn += toSpawn;
    if (!(rand() % 4)) {
        increment(30);
    }
}

Move *Spawner::action(Map &map)
{
    if(aboveZero()) {
        decrement();
        return next;
    } else if (toSpawn <= 0) {
        return next;
    }

    unsigned int i;
    int r, c, delay;
    double dist;

    i = min((unsigned int) 5 + round, toSpawn);
    toSpawn -= i;
    delay = 50 + (5 * i);

    int tries = 0;
    while (i-- > 0) {
        do {
            r = rand() % height;
            c = rand() % width;
        } while ((
            map.board[r][c]->getCost() == INT_MAX || 
            map.sprites[r][c] || 
            map.bz_path[r][c].cost == INT_MAX ||
            (dist = sqrt(pow(map.pc->row - r, 2.0) + pow(map.pc->col - c, 2.0))) < 12.0 ||
            dist > 50.0
            ) && tries++ < 20);

        // somehow make the zombies get harder over time, this isn't the correct way but it works for now
        map.sprites[r][c] = Zombie::getZombie(r, c, 1, (round * 2) + 15 + rand() % 10, (round * 2) + 50 + rand() % 20);
        map.add_to_list(map.sprites[r][c]);
        map.num_zombies++;
    }

    increment(delay);

    return next;
}
