#ifndef projectile_H
#define projectile_H

#include "sprite.h"
#include "pc.h"

class Projectile: public Sprite {
    public:
        static Projectile *getProjectile(PC &pc, int r, int c, Direction d);
        ~Projectile();
        Move *action(Map &m);
        int getSpeed() { return speed; }
        void upDistance() { distance++; }
    private:
        Projectile(PC &pc, int r, int c, Direction d);
        int speed;
        int range;
        int distance;
        Direction dir;
        PC &pc;
};

#endif
