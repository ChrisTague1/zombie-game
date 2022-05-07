#ifndef pc_H
#define pc_H

#include "sprite.h"

class PC: public Sprite {
    private:
        bool user_input(Map &map);
    public:
        bool on;
        PC(int r, int c);
        ~PC();
        int action(Map &m);
};

bool kbhit(void);

#endif
