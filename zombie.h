#ifndef zombie_H
#define zombie_H

#include "character.h"
#include "visitor.h"

class Zombie: public Character {
    public:
        Zombie(int r, int c);
        ~Zombie();
        int visit(Acceptor &a);
};

#endif
