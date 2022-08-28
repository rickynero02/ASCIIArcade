#pragma once
#include <ncurses.h>
#include "entity.hpp"

class Player : public Entity {

private:
    int max_health;
    bool has_key = false;

public:
    Player(int x, int y);

    void move(WINDOW* win, Position pos) override;
    void setHasKey(bool key);
    bool getHasKey();
};