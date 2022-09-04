
#include "bullet.hpp"
#include "player.hpp"

void Bullet::update(State* state, int t) {
    if (t < 7) {
        int newx = x, newy = y;
        if (dir == direction::xaxis) {
            newx += v;
        } else {
            newy += v;
        }

        if (newy == 0 || newy == 29) {
            mvwaddch(container, y, x, ' ');
            icon = ' ';
            return;
        }

        int ch = mvwinch(container, newy, newx);
        if (ch == ' ' || ch == '+'  || 
            ch == '*' || ch == owner->getIcon()) {
            mvwaddch(container, y, x, ' ');
            x = newx;
            y = newy;
            return;
        }

        if (ch == '|' || ch == '-' || ch == '?' || ch == 'O') {
            mvwaddch(container, y, x, ' ');
            icon = ' ';
            return;
        }

        auto player = state->getPlayer();        

        auto hitted = (player->getIcon() == ch) ?
            player : state->getEntity(newx, newy, ch);

        if ((owner->getIcon() == 'T' && hitted->getIcon() == 'x') 
            || (owner->getIcon() == 'x' && hitted->getIcon() == 'T')) {
            mvwaddch(container, y, x, ' ');
            icon = ' ';
            return;
        }

        hitted->setHealth(hitted->getHealth() - owner->getDamage());
        icon = ' ';
        mvwaddch(container, y, x, ' ');
    }
}

