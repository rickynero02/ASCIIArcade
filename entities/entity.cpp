#include "entity.hpp"
#include "bullet.hpp"

void ActiveEntity::shoot(State* state, char ch) {
    int bpx = (dir == direction::xaxis) ? (x+v) : x;
    int bpy = (dir == direction::yaxis) ? (y+v) : y;

    if (bpy != 0 && bpy != 29) {
        int posch = mvwinch(container, bpy, bpx);
        if (posch == ' ') {
            auto bullet = std::make_shared<Bullet>(container, bpx, bpy, ch, dir, 
                v, shared_from_this());
            state->add(bullet);
        }
    }
}