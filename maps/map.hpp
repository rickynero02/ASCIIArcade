#pragma once
#include <ncurses.h>
#include <memory>

class State;
class Player;
class Info;

class Map {

private:
    const int height = 30;
    const int width = 70;
    const int start_y = 3;
    const int start_x = 12;

    int val_y1, val_x1, val_y2, val_x2; //artefatti
    int x, y, z;   //muri

    WINDOW *win;
    std::shared_ptr<State> state;
    std::unique_ptr<Info> info;

    void createWalls();
    void createDoors();
    void createArtifact();

public:
    Map(std::shared_ptr<Player>);
    ~Map();

    void show();
    WINDOW * getWindow();
    void updateState(int, int);
};