#ifndef zombie_H
#define zombie_H

#include "sprite.h"

class Zombie: public Sprite {
    private:
        Zombie(int r, int c, int health, int odds_moving, int odds_following);
        int odds_moving;
        int odds_following;
    public:
        static Zombie *getZombie(int r, int c, int health, int odds_moving, int odds_following);
        ~Zombie();
        Move *action(Map &m);
        int collide(Sprite *s, Map &map);
        int on_collision(PC *pc, Map &map);
        int on_collision(Zombie *zombie, Map &map);
        int on_collision(Projectile *projectile, Map &map);
        void print(int row, int col);
};

#endif
