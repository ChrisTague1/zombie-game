#ifndef zombie_H
#define zombie_H

#include "sprite.h"
#include "visitor.h"

class Zombie: public Sprite {
    public:
        Zombie(int r, int c);
        ~Zombie();
        int visit(Acceptor &a);
};

#endif
