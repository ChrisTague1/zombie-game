#ifndef sprite_H
#define sprite_H

#include "cell.h"
#include "move.h"

class PC;
class Zombie;
class Projectile;

class Sprite: public Cell, public Move {
    private:
        char c;
    public:
        int row;
        int col;
        char getChar();
        void updatePos(int dy, int dx);
        virtual int collide(Sprite *s, Map &map) = 0;
        virtual int on_collision(PC *pc, Map &map) = 0;
        virtual int on_collision(Zombie *zombie, Map &map) = 0;
        virtual int on_collision(Projectile *projectile, Map &map) = 0;
        Sprite(char ch, int r, int c);
        virtual ~Sprite() {}
};

typedef enum direction {
    up,
    down,
    left,
    right
} Direction;

const int dirs[4][2] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
};

#endif
