#ifndef cell_H
#define cell_H

class Cell {
    public:
        virtual ~Cell() {}
        virtual void print(int row, int col) = 0;
    protected:
        Cell(char c): c(c) {}
        char c;
};

#endif
