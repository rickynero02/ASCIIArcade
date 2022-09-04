#include "artifact.hpp"
#include "player.hpp"

void Artifact::update(State* state, int tick) {
    auto p = state->getPlayer();
    int px = p->getX(), py = p->getY();
    if (x == px && y == py) {
        icon = ' ';
 
        if (b == buff::health) {
            int newhealth = p->getHealth() + (health_buff * t);
            p->setHealth(newhealth);
        } else {
            int newdmg = p->getDamage() + (damage_buff * t);
            p->setDamage(newdmg);
        }
    }
}