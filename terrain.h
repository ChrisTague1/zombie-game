#ifndef terrain_H
#define terrain_H

#include "cell.h"
#include <ncurses.h>
#include "pc.h"

class Terrain: public Cell {
    private:
        int cost;
    public:
        int getCost();
        virtual ~Terrain() {}
        virtual void print(int row, int col) {
            attron(COLOR_PAIR(4));
            mvaddch(row + 1, col + 1, c);
            attroff(COLOR_PAIR(4));
        }
        virtual void interact(PC &pc) {}
    protected:
        Terrain(int cost, char c);
};

class Building: public Terrain {
    public:
        Building();
};

class Grass: public Terrain {
    public:
        Grass();
        void print(int row, int col) {
            attron(COLOR_PAIR(5));
            mvaddch(row + 1, col + 1, c);
            attroff(COLOR_PAIR(5));
        }
};

class Tile: public Terrain {
    public:
        Tile();
};

class Tree: public Terrain {
    public:
        Tree();
};

#endif
