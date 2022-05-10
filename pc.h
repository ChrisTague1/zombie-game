#ifndef pc_H
#define pc_H

#include "sprite.h"

class PC: public Sprite {
    private:
        bool user_input(Map &map);
        PC(int r, int c);
        bool kbhit(void);
        int kills;
        void printStats(void);
    public:
        static PC *getPC(int r, int c);
        bool on;
        ~PC();
        Move *action(Map &m);
        void move(int dy, int dx, Map &map);
        int kill(void);
        unsigned int money;
        int getKills(void) { return kills; }
        int health;
        int collide(Sprite *s, Map &map);
        int on_collision(PC *pc, Map &map);
        int on_collision(Zombie *zombie, Map &map);
        int on_collision(Projectile *projectile, Map &map);
};

#endif
