#ifndef pc_H
#define pc_H

#include "sprite.h"

class PC: public Sprite {
    public:
        bool on;
        PC(int r, int c);
        ~PC();
        int visit(Acceptor &a);
};

bool kbhit(void);

#endif
