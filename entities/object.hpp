#pragma once

#include <ncurses.h>

class State;

class Object {

protected:
    int x, y;
    char icon;
    WINDOW* container;

public:
    Object(WINDOW *w, int x, int y, char icon) : 
        x(x), y(y), icon(icon), container(w) {}

    char getIcon() const { return icon; }
    int getX() const { return x; }
    int getY() const { return y; }

    virtual ~Object() {}

    virtual void update(State* s, int n) {}

    virtual void draw() {
        mvwaddch(container, y, x, icon);
    }
};