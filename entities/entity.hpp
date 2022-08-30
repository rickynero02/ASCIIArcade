#pragma once

#include "object.hpp"
#include "state.hpp"

enum direction {
    xaxis, yaxis
};

enum verse {
    positive = 1, negative = -1
};

class Entity : public Object {

protected:
    direction dir;
    verse v;

public:
    Entity(WINDOW* w, int x, int y, char icon, direction dir, verse v) 
        : Object(w, x, y, icon), dir(dir), v(v) {}
    
    virtual ~Entity() {}
};

class ActiveEntity : public Entity {

protected:
    int health, damage;

public:
    ActiveEntity(WINDOW* w, int x, int y, char icon, 
        direction dir, verse v, int health, int damage)
        : Entity(w, x, y, icon, dir, v), health(health), damage(damage) {}

    virtual ~ActiveEntity() {}

    int getHealth() const { return health; }
    int getDamage() const { return damage; }
    void setHealth(int h) { health = h; }
    void setDamage(int d) { damage = d; }
};