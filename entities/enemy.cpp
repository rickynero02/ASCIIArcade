#include "enemy.hpp"
#include "player.hpp"

void Enemy::move(std::shared_ptr<Player> player) {
    dir = player->getDirection();
    verse pv = player->getVerse();
    int px = player->getX();
    int py = player->getY();

    if (dir == direction::yaxis) {
        if (py < y) {
            v = verse::negative;
        } else if (py > y) {
            v = verse::positive;
        } else {
            dir = direction::xaxis;
            v = (px < x) ? verse::negative : verse::positive;
        }
    } else {
        if (px < x) {
            v = verse::negative;
        } else if (px > x) {
            v = verse::positive;
        } else {
            dir = direction::yaxis;
            v = (py < y) ? verse::negative : verse::positive;
        }
    }


    int newx = (dir == direction::xaxis) ? x + v : x;
    int newy = (dir == direction::yaxis) ? y + v : y;

    int posch = mvwinch(container, newy, newx);
    if (posch == ' ') {
        mvwaddch(container, y, x, ' ');
        x = newx;
        y = newy;
    }
}
 
void BaseEnemy::update(State* state, int t) {   
    if (health <= 0) {
        icon = ' ';
    }

    if (t == 1) {
        auto player = state->getPlayer();
        move(player);

        if (rand() % 5 == 0) {
            shoot(state, '*');
        }
    }
}

void BossEnemy::update(State* state, int t) {
    auto player = state->getPlayer();
    if (health <= 0) {
        icon = ' ';
        player->setHasKey(true);
    }

    if (t == 1) {
        move(player);

        if (rand() % 3 == 0) {
            shoot(state, '*');
        }
    }
}
