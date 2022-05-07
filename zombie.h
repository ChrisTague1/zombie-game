#ifndef zombie_H
#define zombie_H

#include "sprite.h"

class Zombie: public Sprite {
    public:
        Zombie(int r, int c);
        ~Zombie();
        int action(Map &m);
};

#endif
