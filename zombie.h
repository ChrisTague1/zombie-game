#ifndef zombie_H
#define zombie_H

#include "sprite.h"

class Zombie: public Sprite {
    private:
        Zombie(int r, int c);
        char odds_moving;
        char odds_follow;
    public:
        static Zombie *getZombie(int r, int c);
        ~Zombie();
        Move *action(Map &m);
};

#endif
