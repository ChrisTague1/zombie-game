#include "map.h"
#include <cstdlib>
#include "character.h"
#include "zombie.h"
#include "pc.h"
#include <climits>
#include <ncurses.h>
#include <unistd.h>

Map::Map(PC &c): pc(c)
{
    int i, j, z;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            characters[i][j] = NULL;
            if (rand() % 20 == 0) {
                board[i][j] = new Building();
            } else {
                board[i][j] = new Grass();
            }
        }
    }

    z = 1 + rand() % 3;

    while (z--) {
        i = rand() % height;
        j = rand() % width;

        characters[i][j] = new Zombie(i, j);
        list.push_back(characters[i][j]);
    }

    list.push_back(&c);
}

Map::~Map()
{
    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (board[i][j]) {
                delete board[i][j];
            }
            if (characters[i][j]) {
                delete characters[i][j];
            }
        }
    }
}

int Map::move(Character &c, int dy, int dx)
{
    characters[c.row][c.col] = NULL;
    c.updatePos(dy, dx);
    characters[c.row][c.col] = &c;
    c.increment(board[c.row][c.col]->getCost());

    return 0;
}

bool Map::validMove(Character &c, int dy, int dx)
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
