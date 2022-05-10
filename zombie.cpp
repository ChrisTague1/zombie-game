#include "zombie.h"
#include <cstdlib>
#include "map.h"
#include "ncurses.h"

Zombie::Zombie(int r, int c): Sprite('Z', r, c)
{
    odds_moving = 15 + rand() % 10;
    odds_follow = 50 + rand() % 20;
}

Zombie::~Zombie()
{}

Zombie *Zombie::getZombie(int r, int c)
{
    return new Zombie(r, c);
}

Move *Zombie::action(Map &map)
{
    if (aboveZero()) {
        decrement();
        return next;
    }
    
    if (rand() % 100 > odds_moving) return next;

    int n;

    for (n = 0; n < 4; n++) {
        if (map.sprites[row + dirs[n][0]][col + dirs[n][1]] == map.pc) {
            increment(10);
            map.pc->health--;
            return next;
        }
    }

    n = rand() % 4;

    if (rand() % 100 > odds_follow) {
        map.validMove(*this, dirs[n][0], dirs[n][1]) && 
        map.emptySpace(*this, dirs[n][0], dirs[n][1]) && 
        map.move(*this, dirs[n][0], dirs[n][1]);
    } else {
        map.emptySpace(*this, map.bz_path[row][col].to.row, map.bz_path[row][col].to.col) && 
        map.move(*this, map.bz_path[row][col].to.row, map.bz_path[row][col].to.col);
    }

    return next;
}

int Zombie::collide(Sprite *s, Map &map)
{ return s->on_collision(this, map); }

int Zombie::on_collision(PC *pc, Map &map)
{
    return 0; // stuff will go here
}

int Zombie::on_collision(Zombie *zombie, Map &map)
{ return 0; }

int Zombie::on_collision(Projectile *projectile, Map &map)
{
    map.pc->kill();
    map.destroy(this);
    map.num_zombies--;
    return 0; // stuff will go here
}
