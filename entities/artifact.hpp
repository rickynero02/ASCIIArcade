#pragma once

#include "object.hpp"

class Artifact : public Object {

public:
    Artifact(WINDOW* w, int x, int y) : 
        Object(w, x, y, '?') {}
};