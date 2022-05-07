#ifndef move_H
#define move_H

class Map;

class Move {
    public:
        bool aboveZero();
        void decrement();
        void increment(char i);
        virtual ~Move() {}
        Move *prev;
        Move *next;
        virtual int action(Map &m) = 0;
    protected:
        Move();
        char movement;
};

#endif
