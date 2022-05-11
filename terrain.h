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
        Terrain(int cost, char c);
};

class Building: public Terrain {
    public:
        Building();
};

class Grass: public Terrain {
    public:
        Grass();
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
