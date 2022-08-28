#include <string>
#include <ncurses.h>
#include "player.hpp"

Player::Player(int x, int y) : Entity() {
    position.x = x;
    position.y = y;
    health = 20;
    max_health = 20;
    damage = 2;
    icon = 'P';
    bullet_icon = '-';
}

void Player::move(WINDOW* win, Position pos) {
    //Prendo il carattere nella posizione in cui mi voglio muovere
    //Se ho spazio mi muovo altrimenti no
    int ch = mvwinch(win, pos.y, pos.x); 
    if (ch == ' ') {
        position = pos;
    }
}

void Player::setHasKey(bool key) {
    has_key = key;
}

bool Player::getHasKey() {
    return has_key;
}