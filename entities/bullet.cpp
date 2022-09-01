
#include "bullet.hpp"
#include "player.hpp"

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
        if (ch == ' ' || ch == '+' 
            || ch == '*' || ch == owner->getIcon()) {
            x = newx;
            y = newy;
            return;
        }

        if (ch == '|' || ch == '-' || ch == '?' || ch == 'O') {
            icon = ' ';
            return;
        }

        auto hitted = (state->getPlayer()->getIcon() == ch) ?
            state->getPlayer() : state->getEntity(newx, newy, ch);

        hitted->setHealth(hitted->getHealth() - owner->getDamage());
        icon = ' ';
    }
}

