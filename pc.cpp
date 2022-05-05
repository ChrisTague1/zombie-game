#include "pc.h"
#include <ncurses.h>

PC::PC(int r, int c): Sprite('@', r, c)
{
    on = true;
}

PC::~PC()
{}

int PC::visit(Acceptor &a)
{
    a.accept(*this);
    return 0;
}

bool kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return true;
    } else {
        return false;
    }
}
