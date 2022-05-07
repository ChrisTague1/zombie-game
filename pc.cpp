#include "pc.h"
#include <ncurses.h>
#include "map.h"

PC::PC(int r, int c): Sprite('@', r, c)
{
    on = true;
}

PC::~PC()
{}

bool kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return true;
    } else {
        return false;
    }
}

typedef enum direction {
    up = 119,
    down = 115,
    left = 97,
    right = 100
} Direction;

bool PC::user_input(Map &map)
{
    int ch = getch();
    flushinp();

    switch (ch) {
        case 113:
            return false;
        case up:
            map.validMove(*this, dirs[0][0], dirs[0][1]) && map.move(*this, dirs[0][0], dirs[0][1]);
            break;
        case down:
            map.validMove(*this, dirs[1][0], dirs[1][1]) && map.move(*this, dirs[1][0], dirs[1][1]);
            break;
        case left:
            map.validMove(*this, dirs[2][0], dirs[2][1]) && map.move(*this, dirs[2][0], dirs[2][1]);
            break;
        case right:
            map.validMove(*this, dirs[3][0], dirs[3][1]) && map.move(*this, dirs[3][0], dirs[3][1]);
            break;
        default:
            break;
    }

    return true;
}

int PC::action(Map &map)
{
    if (kbhit()) {
        on = user_input(map);
    }

    return 0;
}
