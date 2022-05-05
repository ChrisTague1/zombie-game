#ifndef move_H
#define move_H

class Move {
    public:
        bool aboveZero();
        void decrement();
        void increment(char i);
        virtual ~Move() {}
    protected:
        Move();
        char movement;
};

#endif
