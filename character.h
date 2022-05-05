#ifndef character_H
#define character_H

#include "cell.h"
#include "move.h"
#include "visitor.h"

class Character: public Move, public Cell, public Visitor {
    private:
        char c;
    public:
        int row;
        int col;
        char getChar();
        void updatePos(int dy, int dx);
        Character(char ch, int r, int c);
        ~Character();
};

const int dirs[4][2] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
};

#endif
