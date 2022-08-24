#pragma once
#include <ncurses.h>
#include "entity.hpp"

class Player : public Entity {

private:
    WINDOW *win;
    int max_health;

public:
    Player(int x, int y);

    void move(Position pos) override;
};