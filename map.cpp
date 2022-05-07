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

int Map::remove_from_list(Move *v) // never give it a null node, it doesn't check for that
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

int Map::add_to_list(Move *v) // never give it a null node, it doesn't check for that
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

Map::Map()
{
    list = NULL;
    list_tail = NULL;

    int i, j, z;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            sprites[i][j] = NULL;
            if (rand() % 20 == 0) {
                board[i][j] = new Building();
            } else {
                board[i][j] = new Grass();
            }
        }
    }

    z = 10 + rand() % 30;

    while (z--) {
        i = rand() % height;
        j = rand() % width;

        sprites[i][j] = Zombie::getZombie(i, j);
        add_to_list(sprites[i][j]);
    }

    pc = PC::getPC(height / 2, width / 2);
    sprites[pc->row][pc->col] = pc;

    add_to_list(pc);
    board[pc->row][pc->col] = new Grass();

    generate_path(bz_path);
}

static int32_t path_comp(const void *key, const void *with) {
	return ((path_t *) key)->cost - ((path_t *) with)->cost;
}

void Map::generate_path(path_t path[height][width])
{
    int32_t c;
    path_t *p;
    heap_t h;
    int i, j;
    static int rowVals[] = {-1, 1, 0, 0};
    static int colVals[] = {0, 0, -1, 1};

    for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			path[i][j].pos.row = i;
			path[i][j].pos.col = j;
			if (pc == sprites[i][j]) {
				path[i][j].cost = 0;
			} else {
				path[i][j].cost = INT_MAX;
			}
			path[i][j].hn = NULL;
		}
	}

    heap_init(&h, path_comp, NULL);

    for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (board[i][j]->getCost() != INT_MAX) {
				path[i][j].hn = heap_insert(&h, &path[i][j]);
			} else {
				path[i][j].hn = NULL;
			}
		}
	}

    while ((p = (path_t *) heap_remove_min(&h))) {
		p->hn = NULL;
		c = p->cost + board[p->pos.row][p->pos.col]->getCost();

		for (i = 0; i < 4; i++) {
			if (
                0 <= p->pos.row + rowVals[i] && p->pos.row + rowVals[i] < height &&
                0 <= p->pos.col + colVals[i] && p->pos.col + colVals[i] < width &&
				path[p->pos.row + rowVals[i]][p->pos.col + colVals[i]].hn != NULL &&
				path[p->pos.row + rowVals[i]][p->pos.col + colVals[i]].cost > c
				)
			{
				path[p->pos.row + rowVals[i]][p->pos.col + colVals[i]].cost = c;
				path[p->pos.row + rowVals[i]][p->pos.col + colVals[i]].to.row = p->pos.row;
				path[p->pos.row + rowVals[i]][p->pos.col + colVals[i]].to.col = p->pos.col;
				heap_decrease_key_no_replace(&h, path[p->pos.row + rowVals[i]][p->pos.col + colVals[i]].hn);
			}
		}
	}

    path[pc->row][pc->col].to.col = pc->col;
    path[pc->row][pc->col].to.row = pc->row;
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

int Map::move(Sprite &c, int dy, int dx)
{
    sprites[c.row][c.col] = NULL;
    mvaddch(c.row + 1, c.col + 1, board[c.row][c.col]->getChar());
    c.updatePos(dy, dx);
    sprites[c.row][c.col] = &c;
    mvaddch(c.row + 1, c.col + 1, c.getChar());
    c.increment(board[c.row][c.col]->getCost());

    return 0;
}

int Map::moveTo(Sprite &c, int y, int x)
{
    sprites[c.row][c.col] = NULL;
    mvaddch(c.row + 1, c.col + 1, board[c.row][c.col]->getChar());
    c.row = y;
    c.col = x;
    sprites[c.row][c.col] = &c;
    mvaddch(c.row + 1, c.col + 1, c.getChar());
    c.increment(board[c.row][c.col]->getCost());

    return 0;
}

int Map::move(Projectile &c, int dy, int dx)
{
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
        !c.aboveZero() &&
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

void printPath(path_t path[height][width])
{

    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%d ", path[i][j].cost);
        }
        printf("\n");
    }
}
