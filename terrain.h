#ifndef terrain_H
#define terrain_H

#include "cell.h"

class Terrain: public Cell {
    private:
        int cost;
    public:
        int getCost();
        virtual ~Terrain() {}
    protected:
        Terrain(int cost);
};

class Building: public Terrain {
    public:
        Building();
        char getChar();
};

class Grass: public Terrain {
    public:
        Grass();
        char getChar();
};

class Tile: public Terrain {
    public:
        Tile();
        char getChar();
};

class Tree: public Terrain {
    public:
        Tree();
        char getChar();
};

#endif
