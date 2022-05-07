#include "map.h"
#include <cstdlib>
#include "sprite.h"
#include "zombie.h"
#include "pc.h"
#include <climits>
#include <ncurses.h>
#include <unistd.h>

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
        // list_tail->next = v;
        // v->prev = list_tail; // for some reason when I add to the end, I get a seg fault. Maybe investigate this later
        // list_tail = v;
        v->next = list;
        list->prev = v;
        list = v;
    }

    return 0;
}

Map::Map(PC *c)
{
    list = NULL;
    list_tail = NULL;
    pc = c;

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

    add_to_list(pc);
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

int Map::moveProj(Sprite &c, int dy, int dx)
{
    sprites[c.row][c.col] = NULL;
    mvaddch(c.row + 1, c.col + 1, board[c.row][c.col]->getChar());
    c.updatePos(dy, dx);
    sprites[c.row][c.col] = &c;
    mvaddch(c.row + 1, c.col + 1, c.getChar());

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
        board[c.row + dy][c.col + dx]->getCost() != CHAR_MAX
    );
}
