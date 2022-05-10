#include "projectile.h"
#include "map.h"
#include "ncurses.h"
#include "pc.h"
#include <cstdlib>

Projectile::Projectile(PC *pc, int r, int c, Direction d, int health): Sprite('+', r, c, health), pc(pc), speed(1), range(15), distance(0), dir(d)
{}

Projectile::~Projectile()
{}

Projectile *Projectile::getProjectile(PC *pc, int r, int c, Direction d, int health)
{
    return new Projectile(pc, r, c, d, health);
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
    pc->kill();
    zombie->health--;
    map.num_zombies--;
    health--;
    return 0;
}

int Projectile::on_collision(Projectile *projectile, Map &map)
{ return 0; }
