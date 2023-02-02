#ifndef weapon_H
#define weapon_H

#include "move.h"
#include "direction.h"

class PC;

class Weapon: public Move {
    private:
        PC &pc;
        int speed;
        int range;
        int damage;
        int health;
        int fireRate;
        int ammo;
        Weapon(PC &pc, int speed, int range, int damage, int health, int fireRate, int ammo);
    public:
        Move *action(Map &map);
        virtual ~Weapon() {}
        static Weapon *getWeapon(PC &pc, int speed, int range, int damage, int health, int fireRate, int ammo);
        int shoot(Direction d, Map &map);
        int getAmmo();
        void refillAmmo(int ammo);
};

#endif
