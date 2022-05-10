#include "projectile.h"
#include "map.h"
#include "ncurses.h"
#include "pc.h"
#include <cstdlib>

Projectile::Projectile(PC &pc, int r, int c, Direction d): Sprite('+', r, c), speed(1), range(15), distance(0), dir(d), pc(pc)
{}

Projectile::~Projectile()
{}

Projectile *Projectile::getProjectile(PC &pc, int r, int c, Direction d)
{
    return new Projectile(pc, r, c, d);
}

Move *Projectile::action(Map &m)
{
    if (aboveZero()) {
        decrement();
        return next;
    }
    
    Sprite *target;

    if (distance < range && m.validMove(*this, dirs[dir][0], dirs[dir][1])) {
        if ((target = m.sprites[row + dirs[dir][0]][col + dirs[dir][1]])) {
            pc.kill();
            m.destroy(target);
            m.num_zombies--;
            return m.destroy(this);
        }
        m.move(*this, dirs[dir][0], dirs[dir][1]);
    } else {
        return m.destroy(this);
    }

    return next;
}
