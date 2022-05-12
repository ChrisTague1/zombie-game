#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include "map.h"
#include <cstdio>
#include <climits>

#define frame_rate 31250 // 31250
#define R1_ZOMBIES 7

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
    Map map = Map(R1_ZOMBIES);
    print_board(map);
    // mvprintw(0, 0, "%d", seed);

    Move *current = NULL;

    while (map.pc->on) {
        if (map.shouldContinue()) {
            map.nextRound();
        }
        current = map.list;

        while (current) {
            current = current->action(map);
        }
        
        usleep(frame_rate);
        mvprintw(0, 0, "+--------------------------------------------------");
        mvprintw(0, 0, "Round: %d | Zombies: %d | Zombies in round: %d", map.round, map.num_zombies, map.zombies_in_round);
    }

    mvprintw(height + 1, width / 2 - 5, "Game over.");
    while(getch() != 113);

    endwin();
    return 0;
}
