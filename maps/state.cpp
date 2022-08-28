#include "state.hpp"

State::State() {
    player = new Player(15, 28);
    win = newwin(7, 18, 25, 90);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
}

State::~State() {
    delete player;
    delwin(win);
}

Player* State::getPlayer() {
    return player;
}

void State::show() {
    Position pos = player->getPosition();
    mvwprintw(win, 1, 1, "Player info: ");
    mvwprintw(win, 2, 1, "Health: %03d", player->getHealth());
    mvwprintw(win, 3, 1, "Damage: %03d", player->getDamage());
    mvwprintw(win, 4, 1, "Has Key: %s", player->getHasKey() ? "YES" : "NO");
    mvwprintw(win, 5, 1, "X: %03d - Y: %03d", pos.x, pos.y);
    wrefresh(win);
}