#ifndef projectile_H
#define projectile_H

#include "sprite.h"

class Projectile: public Sprite {
    public:
        static Projectile *getProjectile(int r, int c, Direction d);
        ~Projectile();
        int action(Map &m);
    private:
        Projectile(int r, int c, Direction d);
        int speed;
        int range;
        int distance;
        Direction dir;
};

#endif
