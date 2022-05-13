#include "zombie.h"
#include <cstdlib>
#include "map.h"
#include <ncurses.h>

Zombie::Zombie(
    int r, 
    int c, 
    int health, 
    int odds_moving, 
    int odds_following
    ): Sprite('Z', r, c, health), odds_moving(odds_moving), odds_following(odds_following)
{}

Zombie::~Zombie()
{}

Zombie *Zombie::getZombie(int r, int c, int health, int odds_moving, int odds_following)
{
    return new Zombie(r, c, health, odds_moving, odds_following);
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

    if (rand() % 100 > odds_following) {
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

void Zombie::print(int row, int col)
{
    attron(COLOR_PAIR(2));
    mvaddch(row + 1, col + 1, c);
    attroff(COLOR_PAIR(2));
}
