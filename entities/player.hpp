#pragma once

#include "entity.hpp"

class Player : public ActiveEntity {

private:
    bool hasKey;
    void updatePosition();    

public:
    Player(WINDOW* w, int x, int y) 
        : ActiveEntity(w, x, y, '@', 
        direction::xaxis, verse::positive, 20, 2), hasKey(false) {}
    void update(State*, int) override;

    void setHasKey(bool hasKey) { hasKey = hasKey; }
    bool getHasKey() const { return hasKey; }
};