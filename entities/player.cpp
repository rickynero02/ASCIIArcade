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
    win = newwin(1, 1, 0, 0);
}

void Player::move(Position pos) {

}

void Player::setHasKey(bool key) {
    has_key = key;
}

bool Player::getHasKey() {
    return has_key;
}