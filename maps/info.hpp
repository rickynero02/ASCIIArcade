#pragma once

#include "../entities/state.hpp"
#include <ncurses.h>

class Info {

private:
    std::shared_ptr<State> state;
    WINDOW* win;

public:
    Info(std::shared_ptr<State> s) : state(s) {
        win = newwin(8, 18, 25, 90);
    }

    ~Info() {
        delwin(win);
    }

    void updateInfo();
};