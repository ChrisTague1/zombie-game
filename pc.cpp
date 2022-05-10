#include "pc.h"
#include <ncurses.h>
#include "map.h"
#include "projectile.h"

PC::PC(int r, int c, int health): Sprite('@', r, c, health), kills(0), money(0)
{
    on = true;
}

PC::~PC()
{}

PC *PC::getPC(int r, int c, int health)
{
    static PC *pc;

    if (!pc) {
        pc = new PC(r, c, health);
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
            map.validMove(*this, 0, -1) && map.add_to_list(Projectile::getProjectile(this, row, col - 1, left, 1));
            break;
        case 105: // shoot up
            map.validMove(*this, -1, 0) && map.add_to_list(Projectile::getProjectile(this, row - 1, col, up, 1));
            break;
        case 107: // shoot down
            map.validMove(*this, 1, 0) && map.add_to_list(Projectile::getProjectile(this, row + 1, col, down, 1));
            break;
        case 108: // shoot right
            map.validMove(*this, 0, 1) && map.add_to_list(Projectile::getProjectile(this, row, col + 1, right, 1));
            break;
        default:
            break;
    }

    return true;
}

void PC::move(int dy, int dx, Map &map)
{
    if (map.validMove(*this, dy, dx) && map.emptySpace(*this, dy, dx)) {
        map.move(*this, dy, dx);
        map.generate_path(map.bz_path);
    }
}

Move *PC::action(Map &map)
{
    printStats();
    kbhit();

    if (health <= 0) {
        on = false;
        return next;
    }

    if (aboveZero()) {
        decrement();
    } else if (kbhit()) {
        on = user_input(map);
    }

    return next;
}

int PC::kill(void)
{
    money++;
    return ++kills;
}

void PC::printStats(void)
{
    mvprintw(height + 2, 0, "                                    ");
    mvprintw(height + 2, 0, "Kills: %d | Health: %d | Money %d", kills, health, money);
}

int PC::collide(Sprite *s, Map &map)
{ return s->on_collision(this, map); }

int PC::on_collision(PC *pc, Map &map)
{ return 0; }

int PC::on_collision(Zombie *zombie, Map &map)
{ return 0; }

int PC::on_collision(Projectile *projectile, Map &map)
{ return 0; }
