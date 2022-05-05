#ifndef terrain_H
#define terrain_H

#include "cell.h"

class Terrain: public Cell {
    private:
        char cost;
    public:
        char getCost();
        virtual ~Terrain() {}
    protected:
        Terrain(char cost);
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

#endif
