#ifndef projectile_H
#define projectile_H

#include "sprite.h"

class Projectile: public Sprite {
    public:
        static Projectile *getProjectile(int r, int c, Direction d, int health, int speed, int range, int damage);
        ~Projectile();
        Move *action(Map &m);
        int getSpeed() { return speed; }
        void upDistance() { distance++; }
        int collide(Sprite *s, Map &map);
        int on_collision(PC *pc, Map &map);
        int on_collision(Zombie *zombie, Map &map);
        int on_collision(Projectile *projectile, Map &map);
        void print(int row, int col);
    private:
        Projectile(int r, int c, Direction d, int health, int speed, int range, int damage);
        int speed;
        int range;
        int distance;
        int damage;
        Direction dir;
};

#endif
