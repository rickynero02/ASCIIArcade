#pragma once

#include "entity.hpp"

class Player : public ActiveEntity {

private:
    bool hasKey = false;
    void updatePosition();

public:
    bool loadNextMap = false;
    bool loadPreviousMap = false;
    bool isDead = false;

    Player() : ActiveEntity(nullptr, 0, 0, '@', 
        direction::xaxis, verse::positive, 20, 2) {}
    void update(State*, int) override;

    void setHasKey(bool hk) { hasKey = hk; }
    bool getHasKey() const { return hasKey; }

    void setWindow(WINDOW* w) {
        container = w;
        x = (loadPreviousMap) ? 14 : 15;
        y = (loadPreviousMap) ? 1 : 28 ;
    }
};