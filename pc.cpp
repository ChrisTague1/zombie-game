#include "pc.h"
#include <ncurses.h>
#include "map.h"
#include "projectile.h"

PC::PC(int r, int c): Sprite('@', r, c)
{
    on = true;
}

PC::~PC()
{}

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

bool PC::user_input(Map &map)
{
    int ch = getch();
    flushinp();

    switch (ch) {
        case 113:
            return false;
        case 119:
            map.validMove(*this, dirs[up][0], dirs[up][1]) && map.move(*this, dirs[up][0], dirs[up][1]);
            break;
        case 115:
            map.validMove(*this, dirs[down][0], dirs[down][1]) && map.move(*this, dirs[down][0], dirs[down][1]);
            break;
        case 97:
            map.validMove(*this, dirs[left][0], dirs[left][1]) && map.move(*this, dirs[left][0], dirs[left][1]);
            break;
        case 100:
            map.validMove(*this, dirs[right][0], dirs[right][1]) && map.move(*this, dirs[right][0], dirs[right][1]);
            break;
        case 106: // shoot left
            map.add_to_list(Projectile::getProjectile(row, col - 1, left));
            break;
        case 105: // shoot up
            map.add_to_list(Projectile::getProjectile(row - 1, col, up));
            break;
        case 107: // shoot down
            map.add_to_list(Projectile::getProjectile(row + 1, col, down));
            break;
        case 108: // shoot right
            map.add_to_list(Projectile::getProjectile(row, col + 1, right));
            break;
        default:
            break;
    }

    return true;
}

Move *PC::action(Map &map)
{
    if (kbhit()) {
        on = user_input(map);
    }

    return next;
}
