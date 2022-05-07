#ifndef map_H
#define map_H

#include "terrain.h"
#include "size.h"
#include "sprite.h"
#include "pc.h"
#include "zombie.h"
#include "move.h"
#include "projectile.h"

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
        int move(Projectile &c, int dy, int dx);
        bool validMove(Sprite &c, int dy, int dx);
        PC *pc;
        Move *destroy(Sprite *s);
        Map(PC *c);
        ~Map();
};

#endif
