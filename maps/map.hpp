#pragma once
#include <ncurses.h>

class Map {

private:
    const int height = 30;
    const int width = 70;
    const int start_y = 3;
    const int start_x = 12;

    WINDOW *win;

    void createWalls();
    void createDoors();

public:
    Map();
    ~Map();

    void show();
};