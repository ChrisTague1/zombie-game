#include "shop.h"

Shop::Shop(): Terrain(3, 'S') {}

void Shop::interact(PC &pc) {
    if (pc.money >= 50) {
        pc.health += 10;
        pc.refillAmmo(100);
        pc.money -= 50;
    }
}
