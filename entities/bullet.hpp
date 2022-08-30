#pragma once

#include "entity.hpp"

class Bullet : public Entity {

public:
    Bullet(WINDOW * w, int x, int y, char icon, direction dir, verse v) 
        : Entity(w, x, y, icon, dir, v) {}
    void update(State* state, int t) override;
};