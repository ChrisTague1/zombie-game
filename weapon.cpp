#include "weapon.h"
#include "map.h"
#include "pc.h"

Weapon::Weapon(
    PC &pc,
    int speed,
    int range,
    int damage,
    int health,
    int fireRate
    ): pc(pc), speed(speed), range(range), damage(damage), health(health), fireRate(fireRate)
{}

Weapon *Weapon::getWeapon(PC &pc, int speed, int range, int damage, int health, int fireRate)
{
    return new Weapon(pc, speed, range, damage, health, fireRate);
}

Move *Weapon::action(Map &map)
{ return this; }

int Weapon::shoot(Direction d, Map &map)
{
    if (!map.validMove(pc, dirs[d][0], dirs[d][1])) return -1;

    Projectile *proj = Projectile::getProjectile(pc.row + dirs[d][0], pc.col + dirs[d][1], d, health, speed, range, damage);
    map.add_to_list(proj);
    increment(fireRate);
    if (map.sprites[proj->row][proj->col]) {
        proj->collide(map.sprites[proj->row][proj->col], map);
    }

    return 0;
}
