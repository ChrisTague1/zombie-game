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

PC *PC::getPC(int r, int c)
{
    static PC *pc;

    if (!pc) {
        pc = new PC(r, c);
    }

    return pc;
}

bool PC::kbhit(void)
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
            move(dirs[up][0], dirs[up][1], map);
            break;
        case 115:
            move(dirs[down][0], dirs[down][1], map);
            break;
        case 97:
            move(dirs[left][0], dirs[left][1], map);
            break;
        case 100:
            move(dirs[right][0], dirs[right][1], map);
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

void PC::move(int dy, int dx, Map &map)
{
    if (map.validMove(*this, dy, dx) && !aboveZero()) {
        map.move(*this, dy, dx);
        map.generate_path(map.bz_path);
    }
}

Move *PC::action(Map &map)
{
    kbhit();

    if (aboveZero()) {
        decrement();
    } else if (kbhit()) {
        on = user_input(map);
    }

    return next;
}
