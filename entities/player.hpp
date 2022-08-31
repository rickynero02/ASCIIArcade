#pragma once

#include "entity.hpp"

class Player : public ActiveEntity {

private:
    bool hasKey;
    void updatePosition();    

public:
    Player() : ActiveEntity(nullptr, 0, 0, '@', 
        direction::xaxis, verse::positive, 20, 2), hasKey(false) {}
    void update(State*, int) override;

    void setHasKey(bool hasKey) { hasKey = hasKey; }
    bool getHasKey() const { return hasKey; }

    void setWindow(WINDOW* w) {
        container = w;
        x = 15;
        y = 28;
    }
};