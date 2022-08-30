
#include "bullet.hpp"

void Bullet::update(State* state, int t) {
    if (t == 10) {
        mvwaddch(container, y, x, ' ');

        int newx = x, newy = y;
        if (dir == direction::xaxis) {
            newx += v;
        } else {
            newy += v;
        }

        int ch = mvwinch(container, newy, newx);
        if (ch == ' ') {
            x = newx;
            y = newy;
        } else {
            icon = ' ';
        }
    }
}