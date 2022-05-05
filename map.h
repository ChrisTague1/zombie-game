#ifndef map_H
#define map_H

#include "terrain.h"
#include "size.h"
#include "sprite.h"
#include "pc.h"
#include <vector>
#include "visitor.h"
#include "zombie.h"
#include "move.h"

class Map: public Acceptor {
    private:
        bool user_input(PC &pc);
    public:
        Terrain *board[height][width];
        Sprite *sprites[height][width];
        std::vector<Visitor*> list;
        int move(Sprite &c, int dy, int dx);
        bool validMove(Sprite &c, int dy, int dx);
        PC &pc;
        Map(PC &c);
        ~Map();
        int accept(Visitor &v);
        int accept(Zombie &z);
        int accept(PC &pc);
};

#endif
