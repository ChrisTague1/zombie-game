#ifndef sprite_H
#define sprite_H

#include "cell.h"
#include "move.h"
#include "visitor.h"

class Sprite: public Cell, public Visitor {
    private:
        char c;
    public:
        int row;
        int col;
        char getChar();
        void updatePos(int dy, int dx);
        Sprite(char ch, int r, int c);
        ~Sprite();
};

const int dirs[4][2] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
};

#endif
