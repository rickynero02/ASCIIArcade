
#include "player.hpp"
#include "bullet.hpp"

void Player::update(State* state, int ch) {
    if (health <= 0) {
        isDead = true;
        return;
    }

    if(y == 0) {
        loadNextMap = true;
        return;
    }

    if (y == 29) {
        loadPreviousMap = true;
        y = 28;
        return;
    }
    
    switch (ch) {
        case KEY_LEFT:
            v = verse::negative;
            dir = direction::xaxis;
            updatePosition();
            break;
        case KEY_RIGHT:
            v = verse::positive;
            dir = direction::xaxis;
            updatePosition();
            break;
        case KEY_UP:
            v = verse::negative;
            dir = direction::yaxis;
            updatePosition();
            break;
        case KEY_DOWN:
            v = verse::positive;
            dir = direction::yaxis;
            updatePosition();
            break;
        case 'f':
            shoot(state, '+');
            break;
    }
}

void Player::updatePosition() {
    mvwaddch(container, y, x, ' ');
    int nx = x, ny = y;
    if (dir == direction::xaxis) {
        nx += v;
    } else {
        ny += v;
    }

    int posch = mvwinch(container, ny, nx);
    if (posch == ' ' || posch == '?') {
        x = nx;
        y = ny;
    }
}