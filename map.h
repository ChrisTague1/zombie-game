#ifndef map_H
#define map_H

#include "terrain.h"
#include "size.h"
#include "sprite.h"
#include "pc.h"
#include "zombie.h"
#include "move.h"

class Map {
    private:
        bool user_input(PC &pc);
        Move *list_tail;
    public:
        Terrain *board[height][width];
        Sprite *sprites[height][width];
        Move *list;
        int add_to_list(Move *v);
        int remove_from_list(Move *v);
        int move(Sprite &c, int dy, int dx);
        int moveProj(Sprite &c, int dy, int dx);
        bool validMove(Sprite &c, int dy, int dx);
        PC *pc;
        Map(PC *c);
        ~Map();
};

#endif
