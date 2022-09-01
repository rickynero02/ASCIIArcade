#include "info.hpp"
#include "../entities/player.hpp"

void Info::updateInfo() {
    auto player = state->getPlayer();
    int x = player->getX();
    int y = player->getY();
    
    mvwprintw(win, 1, 1, "Player info: ");
    mvwprintw(win, 2, 1, "Health: %03d", player->getHealth());
    mvwprintw(win, 3, 1, "Damage: %03d", player->getDamage());
    mvwprintw(win, 4, 1, "Has Key: %5s", player->getHasKey() ? "YES" : "NO");
    mvwprintw(win, 5, 1, "X: %03d - Y: %03d", x, y);
    mvwprintw(win, 6, 1, "Objects: %03d", state->size());
    wrefresh(win);
}