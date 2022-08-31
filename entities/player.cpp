
#include "player.hpp"
#include "bullet.hpp"

void Player::update(State* state, int ch) {
    mvwaddch(container, y, x, ' ');
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
            int bpx = (dir == direction::xaxis) ? (x+v) : x;
            int bpy = (dir == direction::yaxis) ? (y+v) : y;

            int posch = mvwinch(container, bpy, bpx);
            if (posch == ' ') {
                auto bullet = std::make_shared<Bullet>(container, bpx, bpy, '+', dir, v);
                state->add(bullet);
            }
            break;
    }
}

void Player::updatePosition() {
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