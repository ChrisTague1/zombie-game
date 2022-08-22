#include "shop.h"

Shop::Shop(): Terrain(3, 'S') {}

void Shop::interact(PC &pc) {
    if (pc.money >= 100) {
        pc.health += 10;
        pc.money -= 100;
    }
}
