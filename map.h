#ifndef map_H
#define map_H

#include "terrain.h"
#include "size.h"
#include "character.h"
#include "pc.h"
#include <vector>
#include "visitor.h"
#include "zombie.h"

class Map: public Acceptor {
    public:
        Terrain *board[height][width];
        Character *characters[height][width];
        std::vector<Character*> list;
        int move(Character &c, int dy, int dx);
        bool validMove(Character &c, int dy, int dx);
        PC &pc;
        Map(PC &c);
        ~Map();
        int accept(Visitor &v);
        int accept(Zombie &z);
};

#endif
