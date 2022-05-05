#include "zombie.h"
#include <cstdlib>

Zombie::Zombie(int r, int c): Character('Z', r, c)
{}

Zombie::~Zombie()
{}

int Zombie::visit(Acceptor &a)
{
    a.accept(*this);
    return 0;
}
