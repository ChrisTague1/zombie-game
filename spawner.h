#ifndef spawner_H
#define spawner_H

#include "move.h"

class Spawner: public Move {
    public:
        Move *action(Map &m);
        Spawner(int delay, int guarantee, int possible);
        ~Spawner();
    private:
        int delay;
        int guarantee;
        int possible;
};

#endif
