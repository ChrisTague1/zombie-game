#include "zombie.h"
#include <cstdlib>
#include "map.h"
#include "ncurses.h"

Zombie::Zombie(int r, int c, int health): Sprite('Z', r, c, health)
{
    odds_moving = 15 + rand() % 10;
    odds_follow = 50 + rand() % 20;
}

Zombie::~Zombie()
{}

Zombie *Zombie::getZombie(int r, int c, int health)
{
    return new Zombie(r, c, health);
}

Move *Zombie::action(Map &map)
{
    if (aboveZero()) {
        decrement();
        return next;
    } else if (health <= 0) {
        map.pc->kill();
        map.num_zombies--;
        return map.destroy(this);
    }
    
    if (rand() % 100 > odds_moving) return next;

    int n = rand() % 4;

    if (rand() % 100 > odds_follow) {
        map.validMove(*this, dirs[n][0], dirs[n][1]) &&
        map.move(*this, dirs[n][0], dirs[n][1]);
    } else {
        map.move(*this, map.bz_path[row][col].to.row, map.bz_path[row][col].to.col);
    }

    return next;
}

int Zombie::collide(Sprite *s, Map &map)
{ return s->on_collision(this, map); }

int Zombie::on_collision(PC *pc, Map &map)
{ return 0; }

int Zombie::on_collision(Zombie *zombie, Map &map)
{ return 0; }

int Zombie::on_collision(Projectile *projectile, Map &map)
{ return projectile->on_collision(this, map); }
