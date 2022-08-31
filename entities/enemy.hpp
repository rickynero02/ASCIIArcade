#pragma once

#include "entity.hpp"

class BaseEnemy : public ActiveEntity {

public:
    BaseEnemy(WINDOW* w, int x, int y, direction dir, verse v) : 
        ActiveEntity(w, x, y, 'x', dir, v, 10, 1) {}
};

class BossEnemy : public ActiveEntity {

public:
    BossEnemy(WINDOW* w, int x, int y, direction dir, verse v) :
        ActiveEntity(w, x, y, 'X', dir, v, 20, 5) {}
};