#pragma once

#include "entity.hpp"

class Player : public ActiveEntity {

private:
    bool hasKey = false;
    void updatePosition();    

public:
    Player() : ActiveEntity(nullptr, 0, 0, '@', 
        direction::xaxis, verse::positive, 20, 2) {}
    void update(State*, int) override;

    void setHasKey(bool hk) { hasKey = hk; }
    bool getHasKey() const { return hasKey; }

    void setWindow(WINDOW* w) {
        container = w;
        x = 15;
        y = 28;
    }
};