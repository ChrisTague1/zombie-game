#ifndef sprite_H
#define sprite_H

#include "cell.h"
#include "move.h"
#include "direction.h"

class PC;
class Zombie;
class Projectile;

class Sprite: public Cell, public Move {
    public:
        int row;
        int col;
        int health;
        void updatePos(int dy, int dx);
        virtual int collide(Sprite *s, Map &map) = 0;
        virtual int on_collision(PC *pc, Map &map) = 0;
        virtual int on_collision(Zombie *zombie, Map &map) = 0;
        virtual int on_collision(Projectile *projectile, Map &map) = 0;
        Sprite(char ch, int r, int c, int health);
        virtual ~Sprite() {}
};

#endif
