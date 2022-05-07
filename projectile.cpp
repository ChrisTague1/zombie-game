#include "projectile.h"
#include "map.h"
#include "ncurses.h"
#include <cstdlib>

Projectile::Projectile(int r, int c, Direction d): Sprite('+', r, c), speed(1), range(5), distance(0), dir(d)
{}

Projectile::~Projectile()
{}

Projectile *Projectile::getProjectile(int r, int c, Direction d)
{
    return new Projectile(r, c, d);
}

Move *Projectile::action(Map &m)
{
    /**
     * Currently, this is buggy
     * If you shoot into a building, it stops (may or may not be what we want)
     * If our speed is so high we shoot past a zombie into an invalid area in one go, it won't hit
     */

    if (distance < range && m.validMove(*this, dirs[dir][0], dirs[dir][1])) {
        increment(speed);
        distance++;
        m.moveProj(*this, dirs[dir][0], dirs[dir][1]);
    } else {
        return m.destroy(this);
    }

    return next;
}
