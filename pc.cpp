#include "pc.h"

PC::PC(int r, int c): Character('@', r, c)
{
    on = true;
}

PC::~PC()
{}

int PC::visit(Acceptor &a) { return 0; }
