#ifndef shop_H
#define shop_H

#include "terrain.h"

class Shop: public Terrain {
    public:
        Shop();
        void interact(PC &pc);
};

#endif
