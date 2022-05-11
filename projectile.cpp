#include "projectile.h"
#include "map.h"
#include "ncurses.h"
#include "pc.h"
#include <cstdlib>

Projectile::Projectile(
    int r, 
    int c, 
    Direction d, 
    int health, 
    int speed, 
    int range,
    int damage
    ):Sprite('+', r, c, health), speed(speed), range(range), distance(0), damage(damage), dir(d)
{}

Projectile::~Projectile()
{}

Projectile *Projectile::getProjectile(int r, int c, Direction d, int health, int speed, int range, int damage)
{
    return new Projectile(r, c, d, health, speed, range, damage);
}

Move *Projectile::action(Map &m)
{
    if (aboveZero()) {
        decrement();
        return next;
    }

    if (0 < health && distance < range && m.validMove(*this, dirs[dir][0], dirs[dir][1])) {
        m.move(*this, dirs[dir][0], dirs[dir][1]);
    } else {
        return m.destroy(this);
    }

    return next;
}

int Projectile::collide(Sprite *s, Map &map)
{ return s->on_collision(this, map); }

int Projectile::on_collision(PC *pc, Map &map)
{ return 0; }

int Projectile::on_collision(Zombie *zombie, Map &map)
{
    zombie->health -= damage;
    health--;
    if (zombie->health > 0 && health > 0) {
        map.sprites[row][col] = NULL;
        mvaddch(row + 1, col + 1, map.board[row][col]->getChar());
        row = zombie->row;
        col = zombie->col;
    }
    increment(speed);
    return 0;
}

int Projectile::on_collision(Projectile *projectile, Map &map)
{ return 0; }
