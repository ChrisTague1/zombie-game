#include "map.h"
#include <cstdlib>
#include "sprite.h"
#include "zombie.h"
#include "pc.h"
#include <climits>
#include <ncurses.h>
#include <unistd.h>

int Map::remove_from_list(Visitor *v) // never give it a null node, it doesn't check for that
{
    if (v == list) {
        list = v->next;
    } else if (v == list_tail) {
        list_tail = v->prev;
    } else {
        v->prev->next = v->next;
        v->next->prev = v->prev;
    }

    return 0;
}

int Map::add_to_list(Visitor *v) // never give it a null node, it doesn't check for that
{
    if (!list) {
        list = v;
        list_tail = v;
    } else {
        list_tail->next = v;
        v->prev = list_tail;
        list_tail = v;
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

        sprites[i][j] = new Zombie(i, j);
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

int Map::accept(Visitor &v) { return 0; }

int Map::accept(Zombie &z)
{
    if (rand() % 20 == 0) {
        sprites[z.row][z.col] = NULL;
        mvaddch(z.row + 1, z.col + 1, board[z.row][z.col]->getChar());
        remove_from_list(&z);
        delete &z;
        return -1;
    }

    int n;

    if (!(rand() % 10)) {
        n = rand() % 4; // could be calling zombie.move(map) to allow for vistors
        validMove(z, dirs[n][0], dirs[n][1]) && move(z, dirs[n][0], dirs[n][1]);
    }

    return 0;
}

typedef enum direction {
    up = 119,
    down = 115,
    left = 97,
    right = 100
} Direction;

bool Map::user_input(PC &pc)
{
    int ch = getch();
    flushinp();

    switch (ch) {
        case 113:
            return false;
        case up:
            this->validMove(pc, dirs[0][0], dirs[0][1]) && this->move(pc, dirs[0][0], dirs[0][1]);
            break;
        case down:
            this->validMove(pc, dirs[1][0], dirs[1][1]) && this->move(pc, dirs[1][0], dirs[1][1]);
            break;
        case left:
            this->validMove(pc, dirs[2][0], dirs[2][1]) && this->move(pc, dirs[2][0], dirs[2][1]);
            break;
        case right:
            this->validMove(pc, dirs[3][0], dirs[3][1]) && this->move(pc, dirs[3][0], dirs[3][1]);
            break;
        default:
            break;
    }

    return true;
}

int Map::accept(PC &pc)
{
    if (kbhit()) {
        pc.on = user_input(pc);
    }

    return 0;
}
