#include "enemy.hpp"
#include "player.hpp"

void BaseEnemy::update(State* state, int t) {   
    if (t == 1) {
        if (health <= 0) {
            icon = ' ';
        }
    }
}

void BossEnemy::update(State* state, int t) {
    if (t == 1) {
        if (health <= 0) {
            icon = ' ';
            state->getPlayer()->setHasKey(true);
        }
    }
}
