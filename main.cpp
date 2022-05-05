#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <climits>
#include "size.h"
#include "pc.h"
#include "map.h"

#define frame_rate 31250
// 31250
typedef enum direction {
    up = 119,
    down = 115,
    left = 97,
    right = 100
} Direction;

PC pc(height / 2, width / 2);
Map map(pc);

void print_board(void)
{
    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (map.characters[i][j]) {
                mvaddch(i + 1, j + 1, map.characters[i][j]->getChar());
            } else if (map.board[i][j]) {
                mvaddch(i + 1, j + 1, map.board[i][j]->getChar());
            }
        }
    }

    box(stdscr, 0, 0);
}

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

bool user_input()
{
    int ch = getch();
    flushinp();

    switch (ch) {
        case 113:
            return false;
        case up:
            map.validMove(pc, dirs[0][0], dirs[0][1]) && map.move(pc, dirs[0][0], dirs[0][1]);
            break;
        case down:
            map.validMove(pc, dirs[1][0], dirs[1][1]) && map.move(pc, dirs[1][0], dirs[1][1]);
            break;
        case left:
            map.validMove(pc, dirs[2][0], dirs[2][1]) && map.move(pc, dirs[2][0], dirs[2][1]);
            break;
        case right:
            map.validMove(pc, dirs[3][0], dirs[3][1]) && map.move(pc, dirs[3][0], dirs[3][1]);
            break;
        default:
            break;
    }

    return true;
}

int main(int argc, char *argv[])
{
    initscr();
    resizeterm(height + 2, width + 2);
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr, 1);
    nodelay(stdscr, 1);
    refresh();
    srand(time(NULL));

    map.characters[pc.row][pc.col] = &pc;

    while (pc.on) { // could make this a variable inside of player, then put the player with the rest of the characters
        print_board();
        // kbhit();
        
        if (pc.aboveZero()) { // this decrement loop will be important
            pc.decrement();
        }

        if (kbhit()) {
            pc.on = user_input();
        }

        for (auto character: map.list) {
            if (character->aboveZero()) {
                character->decrement();
            } else {
                character->visit(map);
            }
        }
        
        usleep(frame_rate);
    }

    map.characters[pc.row][pc.col] = NULL;

    endwin();
    return 0;
}
