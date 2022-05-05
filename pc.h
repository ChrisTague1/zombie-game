#ifndef pc_H
#define pc_H

#include "character.h"

class PC: public Character {
    public:
        bool on;
        PC(int r, int c);
        ~PC();
        int visit(Acceptor &a);
};

#endif
