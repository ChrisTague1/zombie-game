#ifndef map_H
#define map_H

#include "terrain.h"
#include "size.h"
#include "sprite.h"
#include "pc.h"
#include "zombie.h"
#include "move.h"
#include "projectile.h"
#include "heap.h"
#include "spawner.h"

typedef struct point {
	int row;
	int col;
} point_t;

typedef struct path {
	heap_node_t *hn;
	point_t pos;
	point_t to;
	int cost;
    bool done;
} path_t;

class Map {
    private:
        Move *list_tail;
        void generate_path(path_t path[height][width]);
        void addBuilding(int wall);
        friend class PC;
        Spawner *spawner;
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
        path_t bz_path[height][width];
        unsigned int num_zombies;
        void nextRound(void);
        bool shouldContinue(void);
        int round;
        int zombies_in_round;
        Map(int zombies);
        ~Map();
};

#endif
