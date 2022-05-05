#ifndef visitor_H
#define visitor_H

class Acceptor;

class Visitor {
    public:
        virtual int visit(Acceptor &a) = 0;
        Visitor() {}
        virtual ~Visitor() {}
};

class Zombie;

class Acceptor {
    public:
        virtual int accept(Visitor &v) = 0;
        virtual int accept(Zombie &z) = 0;
        Acceptor() {}
        virtual ~Acceptor() {}
};

#endif
