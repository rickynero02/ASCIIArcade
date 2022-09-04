#pragma once

#include "entity.hpp"

class Player;

class Enemy : public ActiveEntity {

protected:
    virtual void move(std::shared_ptr<Player> player); 

public:
    Enemy(WINDOW* w, int x, int y, direction dir, verse v, 
        char icon, int health, int damage) :
        ActiveEntity(w, x, y, icon, dir, v, health, damage) {}

    virtual ~Enemy() {}
};

class BaseEnemy : public Enemy {

public:
    BaseEnemy(WINDOW* w, int x, int y, direction dir, verse v) : 
        Enemy(w, x, y, dir, v, 'x', 10, 1) {}

    void update(State* state, int t) override;
};

class BossEnemy : public Enemy {

public:
    BossEnemy(WINDOW* w, int x, int y, direction dir, verse v) :
        Enemy(w, x, y, dir, v, 'T', 20, 2) {}

    void update(State* state, int t) override;
};