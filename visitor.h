#ifndef visitor_H
#define visitor_H

#include "move.h"
#include <cstdlib>

class Acceptor;
class Map;

class Visitor: public Move {
    public:
        virtual int visit(Acceptor &a) = 0;
        virtual int action(Map &m) = 0;
        Visitor() {
            next = NULL;
            prev = NULL;
        }
        virtual ~Visitor() {}
        Visitor *next;
        Visitor *prev;
};

class Zombie; // all things that implement visitor (can be accepted by map)
class PC;

class Acceptor {
    public:
        virtual int accept(Visitor &v) = 0;
        virtual int accept(Zombie &z) = 0;
        virtual int accept(PC &pc) = 0;
        Acceptor() {}
        virtual ~Acceptor() {}
};

#endif
