#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include "map.h"
#include <cstdio>
#include <climits>

#define frame_rate 31250
// 31250

void print_board(Map &map)
{
    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (map.sprites[i][j]) {
                mvaddch(i + 1, j + 1, map.sprites[i][j]->getChar());
            } else if (map.board[i][j]) {
                mvaddch(i + 1, j + 1, map.board[i][j]->getChar());
            }
        }
    }

    for (i = 0; i < width + 1; i++) {
        mvaddch(0, i, '-');
        mvaddch(height + 1, i, '-');
    }

    for (i = 0; i < height + 1; i++) {
        mvaddch(i, 0, '|');
        mvaddch(i, width + 1, '|');
    }

    mvaddch(0, 0, '+');
    mvaddch(0, width + 1, '+');
    mvaddch(height + 1, 0, '+');
    mvaddch(height + 1, width + 1, '+');
}

int main(int argc, char *argv[])
{
    initscr();
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr, 1);
    nodelay(stdscr, 1);
    refresh();
    int seed;
    seed = time(NULL);
    srand(seed);
    Map map;
    print_board(map);
    // mvprintw(0, 0, "%d", seed);

    Move *current = NULL;

    while (map.pc->on) {
        current = map.list;

        while (current) {
            current = current->action(map);
        }
        
        usleep(frame_rate);
    }

    endwin();
    return 0;
}
