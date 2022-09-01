#pragma once

#include "entity.hpp"

class Bullet : public Entity {

private:
    std::shared_ptr<ActiveEntity> owner;

public:
    Bullet(WINDOW * w, int x, int y, char icon, 
        direction dir, verse v, std::shared_ptr<ActiveEntity> owner) 
        : Entity(w, x, y, icon, dir, v), owner(owner) {}
    void update(State* state, int t) override;

    std::shared_ptr<ActiveEntity> getOwner() const { return owner; }
};