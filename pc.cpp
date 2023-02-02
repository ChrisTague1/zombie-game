#include "pc.h"
#include <ncurses.h>
#include "map.h"
#include "projectile.h"
#include "weapon.h"

PC::PC(int r, int c, int health): Sprite('@', r, c, health), kills(0), money(0)
{
    on = true;
    weapon = Weapon::getWeapon(*this, 1, 25, 2, 1, 2, 100);
    // speed range damage health fire-rate ammo
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
        case 106:
            !weapon->aboveZero() && weapon->shoot(left, map);
            break;
        case 105:
            !weapon->aboveZero() && weapon->shoot(up, map);
            break;
        case 107:
            !weapon->aboveZero() && weapon->shoot(down, map);
            break;
        case 108:
            !weapon->aboveZero() && weapon->shoot(right, map);
            break;
        case 101:
            while(getch() != 101);
            break;
        case 102: // f
            map.board[row][col]->interact(*this);
            break;
        default:
            break;
    }

    return true;
}

void PC::move(int dy, int dx, Map &map)
{
    if (!aboveZero() && map.validMove(*this, dy, dx) && !map.move(*this, dy, dx)) {
        map.generate_path(map.bz_path);
    }
}

Move *PC::action(Map &map)
{
    printStats();

    if (health <= 0) {
        on = false;
        return next;
    }

    if (weapon->aboveZero()) {
        weapon->decrement();
    }

    if (aboveZero()) {
        decrement();
    }

    if (kbhit()) {
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
    mvprintw(height + 2, 0, "                                                 ");
    mvprintw(height + 2, 0, "Kills: %d | Health: %d | Money %d | Ammo %d", kills, health, money, weapon->getAmmo());
}

void PC::refillAmmo(int ammo) {
    weapon->refillAmmo(ammo);
}

int PC::collide(Sprite *s, Map &map)
{ return s->on_collision(this, map); }

int PC::on_collision(PC *pc, Map &map)
{ return 0; }

int PC::on_collision(Zombie *zombie, Map &map)
{
    zombie->increment(10);
    health--;
    return 0;
}

int PC::on_collision(Projectile *projectile, Map &map)
{ return 0; }

void PC::print(int row, int col)
{
    attron(COLOR_PAIR(1));
    mvaddch(row + 1, col + 1, c);
    attroff(COLOR_PAIR(1));
}
