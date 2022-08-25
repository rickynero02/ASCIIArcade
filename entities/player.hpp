#pragma once
#include <ncurses.h>
#include "entity.hpp"

class Player : public Entity {

private:
    WINDOW *win;
    int max_health;
    bool has_key = false;

public:
    Player(int x, int y);

    void move(Position pos) override;
    void setHasKey(bool key);
    bool getHasKey();
};