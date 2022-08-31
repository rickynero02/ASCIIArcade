#pragma once

#include "object.hpp"

enum buff {
    health,
    damage,
};

enum buff_t {
    bonus = 1,
    malus = -1,
};

class Artifact : public Object {

private:
    buff b;
    buff_t t;

    const int health_buff = 5;
    const int damage_buff = 1;

public:
    Artifact(WINDOW* w, int x, int y, buff b, buff_t t) : 
        Object(w, x, y, '?'), b(b), t(t) {}

    void update(State* state, int t) override;
};