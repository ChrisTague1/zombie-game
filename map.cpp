#include "map.h"
#include <cstdlib>
#include "sprite.h"
#include "zombie.h"
#include "pc.h"
#include <climits>
#include <ncurses.h>
#include <unistd.h>
#include "size.h"
#include <cstdio>
#include "spawner.h"

Map::Map(): num_zombies(0)
{
    list = NULL;
    list_tail = NULL;

    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            sprites[i][j] = NULL;
            if (rand() % 20 == 0) {
                board[i][j] = new Tree();
            } else {
                board[i][j] = new Grass();
            }
        }
    }

    i = 4 + rand() % (height / 8);
    for (j = 0; j < i; j++) {
        addBuilding(i + 1);
    }



    do {
        i = rand() % height;
        j = rand() % width;
    } while(board[i][j]->getCost() == INT_MAX);

    pc = PC::getPC(i, j, 10);
    sprites[pc->row][pc->col] = pc;
    add_to_list(pc);

    generate_path(bz_path);
    add_to_list(new Spawner(100, 1, 3));
}

void Map::addBuilding(int wall)
{
    int r, c, y, x, i, j, s;

    r = 5 + rand() % ((height - 5) / 2);
    c = 5 + rand() % ((width - 5) / 2);

    y = rand() % (height - r);
    x = rand() % (width - c);

    for (i = y; i < y + r; i++) {
        for (j = x; j < x + c; j++) {
            board[i][j] = new Building();
        }
    }

    for (i = y + 1; i < y + r - 1; i++) {
        for (j = x + 1; j < x + c - 1; j++) {
            delete board[i][j];
            board[i][j] = new Tile();
        }
    }

    if (rand() % wall) {
        s = 1 + rand() % (r - 2);
        delete board[y + s][x + c - 1];
        board[y + s][x + c - 1] = new Tile();
    }

    if (rand() % wall) {
        s = rand() % (r - 2);
        delete board[y + s][x];
        board[y + s][x] = new Tile();
    }

    if (rand() % wall) {
        s = rand() % (c - 2);
        delete board[y][x + s];
        board[y][x + s] = new Tile();
    }

    if (rand() % wall) {
        s = rand() % (c - 2);
        delete board[y + r - 1][x + s];
        board[y + r - 1][x + s] = new Tile();
    }
}

Map::~Map()
{
    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (board[i][j]) {
                delete board[i][j];
            }
        }
    }

    while ((list_tail = list->next)) {
        delete list;
        list = list_tail;
    }
}

int Map::remove_from_list(Move *v)
{
    if (v == list) {
        list = v->next;
        list->prev = NULL;
    } else if (v == list_tail) {
        list_tail = v->prev;
        list_tail->next = NULL;
    } else {
        v->prev->next = v->next;
        v->next->prev = v->prev;
    }

    return 0;
}

int Map::add_to_list(Move *v)
{
    if (!list) {
        list = v;
        list_tail = v;
    } else {
        v->next = list;
        list->prev = v;
        list = v;
    }

    return 0;
}

static int32_t path_comp(const void *key, const void *with) {
	return ((path_t *) key)->cost - ((path_t *) with)->cost;
}

void Map::generate_path(path_t path[height][width])
{
    int i, j;
    path_t *p;
    int32_t c;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            path[i][j].pos.row = i;
            path[i][j].pos.col = j;
            path[i][j].to.row = 0;
            path[i][j].to.col = 0;
            path[i][j].cost = INT_MAX;
            path[i][j].hn = NULL;
            path[i][j].done = board[i][j]->getCost() == INT_MAX;
        }
    }

    heap_t h;
    heap_init(&h, path_comp, NULL);

    path[pc->row][pc->col].cost = 0;
    path[pc->row][pc->col].pos.row = pc->row;
    path[pc->row][pc->col].pos.col = pc->col;
    path[pc->row][pc->col].hn = heap_insert(&h, &path[pc->row][pc->col]);

    while ((p = (path_t *) heap_remove_min(&h))) {
        for (i = 0; i < 4; i++) {
            if (
                0 <= p->pos.row + dirs[i][0] && p->pos.row + dirs[i][0] < height &&
                0 <= p->pos.col + dirs[i][1] && p->pos.col + dirs[i][1] < width &&
                !path[p->pos.row + dirs[i][0]][p->pos.col + dirs[i][1]].done
            ) {
                if (!path[p->pos.row + dirs[i][0]][p->pos.col + dirs[i][1]].hn) {
                    path[p->pos.row + dirs[i][0]][p->pos.col + dirs[i][1]].hn = heap_insert(&h, &path[p->pos.row + dirs[i][0]][p->pos.col + dirs[i][1]]);
                }

                if ((c = p->cost + board[p->pos.row][p->pos.col]->getCost()) < path[p->pos.row + dirs[i][0]][p->pos.col + dirs[i][1]].cost) {
                    path[p->pos.row + dirs[i][0]][p->pos.col + dirs[i][1]].cost = c;
                    heap_decrease_key_no_replace(&h, path[p->pos.row + dirs[i][0]][p->pos.col + dirs[i][1]].hn);
                    path[p->pos.row + dirs[i][0]][p->pos.col + dirs[i][1]].to.row = -dirs[i][0];
                    path[p->pos.row + dirs[i][0]][p->pos.col + dirs[i][1]].to.col = -dirs[i][1];
                }
            }
        }

        p->done = true;
    }
}

int Map::move(Sprite &c, int dy, int dx)
{
    if (sprites[c.row + dy][c.col + dx]) {
        c.collide(sprites[c.row + dy][c.col + dx], *this);
        return 1;
    }
    sprites[c.row][c.col] = NULL;
    mvaddch(c.row + 1, c.col + 1, board[c.row][c.col]->getChar());
    c.updatePos(dy, dx);
    sprites[c.row][c.col] = &c;
    mvaddch(c.row + 1, c.col + 1, c.getChar());
    c.increment(board[c.row][c.col]->getCost());

    return 0;
}

int Map::move(Projectile &c, int dy, int dx)
{
    if (sprites[c.row + dy][c.col + dx]) {
        c.collide(sprites[c.row + dy][c.col + dx], *this);
        return 1;
    }
    sprites[c.row][c.col] = NULL;
    mvaddch(c.row + 1, c.col + 1, board[c.row][c.col]->getChar());
    c.updatePos(dy, dx);
    sprites[c.row][c.col] = &c;
    mvaddch(c.row + 1, c.col + 1, c.getChar());
    c.increment(c.getSpeed());
    c.upDistance();

    return 0;
}

bool Map::validMove(Sprite &c, int dy, int dx)
{
    return (
        c.row + dy >= 0 &&
        c.row + dy < height &&
        c.col + dx >= 0 &&
        c.col + dx < width &&
        board[c.row + dy][c.col + dx]->getCost() != INT_MAX
    );
}

Move *Map::destroy(Sprite *s)
{
        Move *returning = s->next;
        sprites[s->row][s->col] = NULL;
        mvaddch(s->row + 1, s->col + 1, board[s->row][s->col]->getChar());
        remove_from_list(s);
        delete s;
        return returning;
}
