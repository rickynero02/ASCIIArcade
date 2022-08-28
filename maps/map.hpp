#pragma once
#include <ncurses.h>
#include "state.hpp"

class Map {

private:
    const int height = 30;
    const int width = 70;
    const int start_y = 3;
    const int start_x = 12;

    State* state;
    WINDOW *win;

    void createWalls();
    void createDoors();

public:
    Map(State *state = nullptr);
    ~Map();

    void show();
    void updateState();

    State* getState();
    WINDOW * getWindow();
};