#ifndef zombie_H
#define zombie_H

#include "sprite.h"

class Zombie: public Sprite {
    private:
        Zombie(int r, int c);
    public:
        static Zombie *getZombie(int r, int c);
        ~Zombie();
        Move *action(Map &m);
};

#endif
