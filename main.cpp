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
    int seed;
    seed = time(NULL);
    printf("%d\n", seed);
    initscr();
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr, 1);
    nodelay(stdscr, 1);
    refresh();
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_BLACK);
    srand(seed);
    Map map = Map(R1_ZOMBIES);
    print_board(map);

    Move *current = NULL;

    while (map.pc->on) {
        if (map.shouldGoToNextRound()) {
            map.nextRound();
        }
        current = map.list;

        while (current) {
            current = current->action(map);
        }
        
        usleep(frame_rate);
        attron(COLOR_PAIR(4));
        mvprintw(0, 0, "+--------------------------------------------------");
        mvprintw(0, 0, "Round: %d | Zombies: %d | Zombies in round: %d", map.round, map.num_zombies, map.zombies_in_round);
        attroff(COLOR_PAIR(4));
    }

    if (map.pc->health <= 0) {
        mvprintw(height + 1, width / 2 - 5, "Game over.");
        while(getch() != 113);
    }

    endwin();
    printf("%d\n", seed);
    return 0;
}
