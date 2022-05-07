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
    Map map;
    print_board(map);

    Move *current = NULL;
    Move *next = NULL;

    while (map.pc->on) {
        kbhit();
        current = map.list;

        while (current) {
            if (current->aboveZero()) {
                current->decrement();
                current = current->next;
            } else {
                next = current->action(map);
            }

            current = next;
        }
        
        usleep(frame_rate);
    }

    endwin();

    // printPath(map.bz_path);
    return 0;
}
