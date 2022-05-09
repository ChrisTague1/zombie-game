#ifndef pc_H
#define pc_H

#include "sprite.h"

class PC: public Sprite {
    private:
        bool user_input(Map &map);
        PC(int r, int c);
        bool kbhit(void);
    public:
        static PC *getPC(int r, int c);
        bool on;
        ~PC();
        Move *action(Map &m);
        void move(int dy, int dx, Map &map);
};

#endif
