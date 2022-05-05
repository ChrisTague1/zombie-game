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

    while (pc.on) {
        print_board();
        kbhit();

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
