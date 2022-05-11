#ifndef direction_H
#define direction_H

typedef enum direction {
    up,
    down,
    left,
    right
} Direction;

const int dirs[4][2] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
};

#endif
