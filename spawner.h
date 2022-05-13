#ifndef spawner_H
#define spawner_H

#include "move.h"

class Spawner: public Move {
    public:
        Move *action(Map &m);
        Spawner(unsigned int zombies, int round);
        ~Spawner();
        void spawn(int round, int toSpawn);
    private:
        int round;
        unsigned int toSpawn;
        friend class Map;
};

#endif
