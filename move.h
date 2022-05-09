#ifndef move_H
#define move_H

class Map;

class Move {
    public:
        bool aboveZero();
        void decrement();
        void increment(int i);
        virtual ~Move() {}
        Move *prev;
        Move *next;
        virtual Move *action(Map &m) = 0;
    protected:
        Move();
        int movement;
};

#endif
