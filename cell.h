#ifndef cell_H
#define cell_H

class Cell {
    private:
        char c;
    public:
        char getChar() { return c; }
        virtual ~Cell() {}
    protected:
        Cell(char c): c(c) {}
};

#endif
