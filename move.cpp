#include "move.h"

bool Move::aboveZero() {
    return movement > 0;
}

void Move::decrement() {
    movement--;
}

void Move::increment(int i) {
    movement += i;
}

Move::Move() {
    movement = 0;
    next = 0;
    prev = 0;
}
